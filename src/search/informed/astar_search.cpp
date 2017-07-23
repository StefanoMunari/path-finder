using std::priority_queue;
using std::map;
using std::vector;
using std::list;
using std::string;
using std::shared_ptr;

#include "heuristics/exact_heuristic.h"

template <typename State>
AStarSearch<State>::AStarSearch() noexcept
{
	this->_informed_qmaker = ColoredInformedQueueMaker<State>();
	this->_informed_map_maker = ColoredInformedMapMaker<State>();
	this->_heuristic = new ExactHeuristic<State>();
}

template <typename State>
AStarSearch<State>::AStarSearch(const AStarSearch& that){
	this->_informed_qmaker = that._informed_qmaker;
	this->_informed_map_maker = that._informed_map_maker;
	this->_heuristic = that._heuristic;
}

template <typename State>
AStarSearch<State>&
AStarSearch<State>::operator=(const AStarSearch& that)
{
	this->_informed_qmaker = that._informed_qmaker;
	this->_informed_map_maker = that._informed_map_maker;
	this->_heuristic = that._heuristic;
	return *this;
}

template <typename State>
AStarSearch<State>::~AStarSearch() noexcept
{
	delete this->_heuristic;
}

template <typename State>
void
AStarSearch<State>::SetHeuristicFunction(HeuristicFunction<State> * heuristic)
{
	if(heuristic != nullptr)
	{
		delete this->_heuristic;
		this->_heuristic = heuristic;
	}
}

template <typename State>
list<State>*
AStarSearch<State>::Solve(Node<State>* last)
{
	Node<State>* iterator = last;
	list<State>* result = new list<State>();
	while(iterator)
	{
		result->push_front(iterator->state);
		iterator = iterator->parent;
	}
	return result;
}

template <typename State>
list<State>*
AStarSearch<State>::Search(
	GraphPtr_IdMap static_graph_,
	shared_ptr<GraphPtr_IdMap> dynamic_graph_,
	const Problem<State>& problem)
{
// declare vars and execute heuristic function
	// boost-property accessors
	IndexMap node_index =
		boost::get(boost::vertex_index, (*static_graph_.first));
	// shortcuts for verbose types
	typedef std::priority_queue<
			std::pair<NodeColored<State>*,  NodeCosts *>,
			std::vector<std::pair<NodeColored<State>*,  NodeCosts *>>,
			NodeComparator<State, NodeCosts>> * InformedQueue;
	typedef map<State, std::pair<NodeColored<State> *, NodeCosts *>> *
			InformedMap;
	// define variables
	Graph * static_graph = static_graph_.first;
	map<State, int> * indexes_map = (map<State, int>*)static_graph_.second;
	auto ids_map = Algorithm::GetReversedMap<State, int>(indexes_map);
	// the resulting path is empty (no solution found yet)
	list<State>* result = EMPTY;
	// compute the informed_map from a search_map
	InformedMap informed_map = EMPTY;
	// compute the contour inserting the source from the informed map
	InformedQueue contour = EMPTY;
	{
		auto search_map_maker = ColoredSearchMapMaker<State>();
		// search map creates the actual colored nodes
		auto search_map = search_map_maker.MakeMap(
					&ids_map,
					static_graph_.first);
		informed_map =
			this->_informed_map_maker.MakeMap(search_map);
		// contour and informed map use only pointers to colored nodes
		// already created in search_map
		contour = this->_informed_qmaker.MakeQueue();
	}
	// update the informed_map with the costs computed by the heuristic
	informed_map =
		this->_heuristic->Eval(
			informed_map, static_graph, indexes_map, ids_map,
			problem.GetGoalState());
	// insert the source node with the correct effective cost,
	// by default all the effective costs are set to MAX
	{
		auto source_node = (*informed_map)[problem.GetFirstState()];
		source_node.second->g = 0;
		// add the source node to the contour
		contour->push(source_node);
	}
	// declare iterators
	VertexDescriptor current, end;
	end = boost::graph_traits<Graph>::null_vertex();

	// apply the A* search algorithm:
	while(!contour->empty() && (current != end)){
		auto current_node = contour->top();
		contour->pop();
		current = (*indexes_map)[current_node.first->state];
		// goal reached - search completed
		if(problem.IsGoal(current_node.first->state)){
			result = Solve(current_node.first);
			break;
		}
		// explore the current area
		auto neighbors =
			boost::adjacent_vertices(current, *static_graph_.first);

		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
			State neighbor = ids_map[node_index[*n_it]];
			auto current_neigh = (*informed_map)[neighbor];
			// <START> mutually shared region (multiple readers)
			std::shared_lock<std::shared_mutex>
				g_lock(path_finder::mutex_graph);
			Graph * dynamic_graph = (dynamic_graph_.get())->first;
			uint dynamic_cost =
				(*dynamic_graph)
				[boost::edge(current,*n_it,(*dynamic_graph)).first];
		   	g_lock.unlock();
			// <END> mutually shared region (multiple readers)
			// neigh.g = parent.g + dynamic_cost(parent, neigh);
			auto effective_neigh_cost =
					current_node.second->g
					+
					dynamic_cost;
			// neighbor not yet explored
			if(current_neigh.second->g > effective_neigh_cost){
		   		current_neigh.first->parent = current_node.first;
		   		current_neigh.second->g = effective_neigh_cost;
		   		contour->push(current_neigh);
			}
		}
	}

	(this->_informed_map_maker.MakeMapDestructor())(informed_map);

	return result;
}