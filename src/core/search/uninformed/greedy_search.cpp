using std::priority_queue;
using std::map;
using std::vector;
using std::list;
using std::shared_ptr;

// G_ prefix for global variables
extern std::shared_mutex G_mutex_graph;

template <typename State>
GreedySearch<State>::GreedySearch() noexcept
{
	this->_map_maker = ColoredSearchMapMaker<State>();
}


template <typename State>
GreedySearch<State>::GreedySearch(const GreedySearch& that) noexcept
{
	this->_map_maker = that._map_maker;
}

template <typename State>
GreedySearch<State>&
GreedySearch<State>::operator=(const GreedySearch& that) noexcept
{
	this->_map_maker = that._map_maker;
	return *this;
}

template <typename State>
list<State>*
GreedySearch<State>::Solve(Node<State>* last) const noexcept
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
GreedySearch<State>::Search(
	GraphPtr_IdMap static_graph_,
	shared_ptr<GraphPtr_IdMap> dynamic_graph_,
	const Problem<State>& problem)
{
	// boost-property accessors
	IndexMap node_index =
		boost::get(boost::vertex_index, (*static_graph_.first));
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;
	// define variables
	Graph * static_graph = static_graph_.first;
	// the resulting path is empty (no solution found yet)
	list<State>* result = EMPTY;
	// state -> vertex_index
	map<State, int>* indexes_map = (map<State, int>*)static_graph_.second;
	// vertex_index -> state
	auto ids_map = Algorithm::GetReversedMap<State, int>(indexes_map);

	// set-up search map
	auto search_map =
		this->_map_maker.MakeMap(&ids_map, static_graph_.first);
	// remove the deprecated source,
	// insert the source node marking it as BLACK (visited/completed)
	{
		auto deprecated_node = (*search_map)[problem.GetFirstState()];
		delete deprecated_node.first;
	}
	(*search_map)[problem.GetFirstState()] =
							SearchableColoredNode(
								new NodeColored<State>(
									problem.GetFirstState(), nullptr, BLACK),0);

	auto current_node = (*search_map)[problem.GetFirstState()];
	State last_explored_state = "";

	while(current_node.first->state != last_explored_state)
	{
		auto current = (*indexes_map)[current_node.first->state];

		// goal reached
		if(problem.IsGoal(current_node.first->state))
		{
			result = Solve(current_node.first);
			break;
		}

		uint min = UINT_MAX;
		last_explored_state = current_node.first->state;
		auto next_node = current_node;

		auto neighbors =
			boost::adjacent_vertices(current, *static_graph_.first);

		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it)
		{
			State neighbor = ids_map[node_index[*n_it]];
			auto current_neigh = (*search_map)[neighbor];

			// node not yet explored
			if(current_neigh.first->color  ==  WHITE)
			{
				// <START> mutually shared region (multiple readers)
				std::shared_lock<std::shared_mutex>
					g_lock(path_finder::G_mutex_graph);

				// read graph
				Graph * dynamic_graph = dynamic_graph_->first;
				uint dynamic_cost =
					(*dynamic_graph)
						[boost::edge(current,*n_it,(*dynamic_graph)).first];

				g_lock.unlock();
				// <END> mutually shared region (multiple readers)
				uint neigh_cost =
					(*static_graph)
					[boost::edge(current,*n_it,(*static_graph)).first]
					+
					dynamic_cost;

				if(neigh_cost < min)
				{
					min = neigh_cost;
					next_node = current_neigh;
				}
			}
		}

		if(next_node != current_node)
		{
			next_node.first->parent = current_node.first;
			next_node.second = current_node.second + min;
			// update search map
			(*search_map)[next_node.first->state] = next_node;
			// move to the current neigh
			current_node = next_node;
		}
		// mark the node as explored
		current_node.first->color = BLACK;
	}

	(this->_map_maker.MakeMapDestructor())(search_map);

	return result;
}