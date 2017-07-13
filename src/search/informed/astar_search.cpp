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
	this->_qmaker = ColoredQueueMaker<State>();
	this->_informed_map_maker = ColoredInformedMapMaker<State>();
	this->_heuristic = new ExactHeuristic<State>();
}

template <typename State>
AStarSearch<State>::AStarSearch(const AStarSearch& that){
	this->_qmaker = that._qmaker;
	this->_informed_map_maker = that._informed_map_maker;
	this->_heuristic = that._heuristic;
}

template <typename State>
AStarSearch<State>&
AStarSearch<State>::operator=(const AStarSearch& that){
	this->_qmaker = that._qmaker;
	this->_informed_map_maker = that._informed_map_maker;
	this->_heuristic = that._heuristic;
	return *this;
}

template <typename State>
AStarSearch<State>::~AStarSearch() noexcept{
	delete this->_heuristic;
}

template <typename State>
void
AStarSearch<State>::SetHeuristicFunction(HeuristicFunction<State> * heuristic){
	if(heuristic != nullptr){
		delete this->_heuristic;
		this->_heuristic = heuristic;
	}
}

template <typename State>
list<State>*
AStarSearch<State>::Solve(Node<State>* last){
	Node<State>* iterator = last;
	list<State>* result = new list<State>();
	while(iterator){
		result->push_front(iterator->state);
		iterator = iterator->parent;
	}
	return result;
}

template <typename State>
list<State>*
AStarSearch<State>::Search(GraphPtr_IdMap static_graph_,
	shared_ptr<GraphPtr_IdMap> dynamic_graph_,
	const Problem<State>& problem)
{
	// boost-property accessors
	IndexMap node_index =
		boost::get(boost::vertex_index, (*static_graph_.first));
	// define variables
	Graph * static_graph = static_graph_.first;
	Graph * dynamic_graph = (dynamic_graph_.get())->first;
	map<string, int> * indexes_map = (map<string, int>*)static_graph_.second;
	auto ids_map = Algorithm::GetReversedMap<string, int>(indexes_map);
	auto contour = this->_qmaker.MakeQueue(problem.GetFirstState());
	// compute the informed_map from a search_map
	map<string, std::pair<NodeColored<State> *, NodeCosts *>> *
		informed_map = nullptr;
	{
		auto search_map = ColoredSearchMapMaker<State>();
		informed_map =
			this->_informed_map_maker.MakeInformedMap(
				search_map.MakeSearchMap(
					(contour->top()).first->state,
					&ids_map,
					static_graph_.first));
	}
	// update the informed_map with the costs computed by the heuristic
	informed_map =
		this->_heuristic->Eval(
			informed_map, static_graph, indexes_map, ids_map,
			problem.GetGoalState());

	// search failed
	return EMPTY;
}