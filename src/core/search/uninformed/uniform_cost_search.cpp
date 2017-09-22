using std::priority_queue;
using std::map;
using std::vector;
using std::list;
using std::shared_ptr;

// G_ prefix for global variables
extern std::shared_mutex G_mutex_graph;

template <typename State>
UniformCostSearch<State>::UniformCostSearch() noexcept
{
	this->_qmaker = ColoredSearchQueueMaker<State>();
	this->_map_maker = ColoredSearchMapMaker<State>();
}

template <typename State>
UniformCostSearch<State>::UniformCostSearch(const UniformCostSearch& that)
noexcept
{
	this->_qmaker = that._qmaker;
	this->_map_maker = that._map_maker;
}

template <typename State>
UniformCostSearch<State>&
UniformCostSearch<State>::operator=(const UniformCostSearch& that)
noexcept
{
	this->_qmaker = that._qmaker;
	this->_map_maker = that._map_maker;
	return *this;
}

template <typename State>
list<State>*
UniformCostSearch<State>::Solve(Node<State>* last)
const noexcept
{
	Node<State> * iterator = last;
	list<State>* result = new list<State>();
	while(iterator){
		result->push_front(iterator->state);
		iterator = iterator->parent;
	}
	return result;
}

template <typename State>
list<State>*
UniformCostSearch<State>::Search(
	GraphPtr_IdMap static_graph_,
	shared_ptr<GraphPtr_IdMap> dynamic_graph_,
	const Problem<State>& problem)
{
	/* boost-property accessors */
	IndexMap node_index =
		boost::get(boost::vertex_index, *(static_graph_.first));
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;
	/* define variables */
	Graph * static_graph = static_graph_.first;
	// the resulting path is empty (no solution found yet)
	list<State>* result = EMPTY;
	// state -> vertex_index
	map<State, int> * indexes_map = (map<State, int>*) static_graph_.second;

	// vertex_index -> state
	auto ids_map = Algorithm::GetReversedMap<State, int>(indexes_map);
	// set-up contour
	auto contour = this->_qmaker.MakeQueue();

	// push the source node and mark it as completed/explored
	contour->push(
		SearchableColoredNode(
			new NodeColored<State>(problem.GetFirstState(), nullptr, BLACK),
			0));
	auto search_map =
		this->_map_maker.MakeMap(&ids_map, static_graph_.first);

	// remove the deprecated source,
	// insert the source node marking it as BLACK (visited/completed) and with
	// cost 0 (it is the source node)
	{
		auto deprecated_node = (*search_map)[problem.GetFirstState()];
		delete deprecated_node.first;
	}
	(*search_map)[problem.GetFirstState()] =
							SearchableColoredNode(
								new NodeColored<State>(
									problem.GetFirstState(), nullptr, BLACK),0);

	// declare iterators
	VertexDescriptor current, end;
	end = boost::graph_traits<Graph>::null_vertex();

	while(!contour->empty() && (current != end))
	{

		auto current_node = contour->top();
		contour->pop();
		current = (*indexes_map)[current_node.first->state];

		// goal reached - search completed
		if(problem.IsGoal(current_node.first->state))
		{
			result = Solve(current_node.first);
			break;
		}
		auto neighbors =
			boost::adjacent_vertices(current, *static_graph);


		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it)
		{
			State neighbor = ids_map[node_index[*n_it]];
			auto current_neigh = (*search_map)[neighbor];
			uint dynamic_cost = 0;
			{
			// <START> mutually shared region (multiple readers)
			std::shared_lock<std::shared_mutex> g_lock(path_finder::G_mutex_graph);
			Graph * dynamic_graph = dynamic_graph_->first;
			dynamic_cost =
				(*dynamic_graph)
	   		[boost::edge(current,*n_it,(*dynamic_graph)).first];
			// <END> mutually shared region (multiple readers)
	   	}
			auto neigh_cost = current_node.second +
					(*static_graph)
					[boost::edge(current,*n_it,(*static_graph)).first]
					+
					dynamic_cost;

			// neighbor not yet explored
			if(current_neigh.first->color  ==  WHITE)
			{
				current_neigh.first->color = GRAY;
		   	current_neigh.first->parent = current_node.first;
		   	current_neigh.second = neigh_cost;
		   	// update search map
		   	(*search_map)[neighbor] = current_neigh;
		   	// insert in contour
		   	contour->push(current_neigh);
			}
			// neighbor has been explored and
			// has an higher cost than the current one
			else if((current_neigh.first->color == GRAY) &&
				(current_neigh.second >= neigh_cost))
			{
				current_neigh.first->parent = current_node.first;
				current_neigh.second = neigh_cost;
		   	// update search map
		   	(*search_map)[neighbor] = current_neigh;
			}
		}
		// mark the node as explored
		current_node.first->color = BLACK;
	}

	(this->_map_maker.MakeMapDestructor())(search_map);

	return result;
}