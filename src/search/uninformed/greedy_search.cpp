using std::priority_queue;
using std::map;
using std::vector;
using std::list;
using std::shared_ptr;

template <typename State>
GreedySearch<State>::GreedySearch() noexcept{
	this->_qmaker = ColoredQueueMaker<State>();
	this->_search_map_maker = ColoredSearchMapMaker<State>();
}


template <typename State>
GreedySearch<State>::GreedySearch(const GreedySearch& that){
	this->_qmaker = that._qmaker;
	this->_search_map_maker = that._search_map_maker;
}

template <typename State>
GreedySearch<State>&
GreedySearch<State>::operator=(const GreedySearch& that){
	this->_qmaker = that._qmaker;
	this->_search_map_maker = that._search_map_maker;
	return *this;
}

template <typename State>
list<State>*
GreedySearch<State>::Solve(Node<State>* last){
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
GreedySearch<State>::Search(
	GraphPtr_IdMap static_graph_,
	shared_ptr<GraphPtr_IdMap> dynamic_graph_,
	const Problem<State>& problem){

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
	// set-up contour
	auto contour = this->_qmaker.MakeQueue();
	// push the source node and mark it as completed/explored
	contour->push(
		SearchableColoredNode(
			new NodeColored<State>(problem.GetFirstState(), nullptr, BLACK),
			0));
	// set-up search map
	auto search_map =
		this->_search_map_maker.MakeMap(&ids_map, static_graph_.first);
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
	// declare iterators
	VertexDescriptor current, end;
	end = boost::graph_traits<Graph>::null_vertex();

	// algorithm
	while(!contour->empty() && (current != end)){
		auto current_node = contour->top();
		contour->pop();
		current = (*indexes_map)[current_node.first->state];
		// goal reached
		if(problem.IsGoal(current_node.first->state)){
			result = Solve(current_node.first);
			break;
		}
		// explore the current area
		auto neighbors =
			boost::adjacent_vertices(current, *static_graph_.first);

		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
			State neighbor = ids_map[node_index[*n_it]];
			auto current_neigh = (*search_map)[neighbor];
			// node not yet explored
			// if a node already exists in the priority queue, then do not
			// insert it another time but keep the first found
			if(current_neigh.first->color  ==  WHITE){
				// mark the node as explored
				current_neigh.first->color = BLACK;
				// <START> mutually shared region (multiple readers)
				std::shared_lock<std::shared_mutex>
					g_lock(path_finder::mutex_graph);
				Graph * dynamic_graph = dynamic_graph_->first;
				uint dynamic_cost =
					(*dynamic_graph)
		   			[boost::edge(current,*n_it,(*dynamic_graph)).first];
		   		g_lock.unlock();
				// <END> mutually shared region (multiple readers)
				auto neigh_cost = current_node.second +
		   			(*static_graph)
		   			[boost::edge(current,*n_it,(*static_graph)).first]
		   			+
		   			dynamic_cost;
		   		current_neigh.first->parent = current_node.first;
		   		current_neigh.second = neigh_cost;
		   		contour->push(current_neigh);
			}
		}
	}

	(this->_search_map_maker.MakeMapDestructor())(search_map);

	return result;
}