using std::priority_queue;
using std::map;
using std::vector;
using std::list;
using std::string;
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
GreedySearch<State>::Search(GraphPtr_IdMap static_graph_,
	shared_ptr<GraphPtr_IdMap> dynamic_graph_,
	const Problem<State>& problem){

	/* boost-property accessors */
	IndexMap node_index =
		boost::get(boost::vertex_index, (*static_graph_.first));
	/* define variables */
	Graph *static_graph = static_graph_.first;
	Graph *dynamic_graph = (dynamic_graph_.get())->first;
	map<string, int>* indexes_map = (map<string, int>*)static_graph_.second;
	auto ids_map = Algorithm::GetReversedMap<string, int>(indexes_map);
	auto contour = this->_qmaker.MakeQueue(problem.GetFirstState());
	auto search_map =
		this->_search_map_maker.MakeSearchMap(
			(contour->top()).first->state, &ids_map, static_graph_.first);
	VertexDescriptor current, end;
	end = boost::graph_traits<Graph>::null_vertex();

	/* body */
	while(!contour->empty() && (current != end)){
		auto current_node = contour->top();
		contour->pop();
		current = (*indexes_map)[current_node.first->state];
		/* goal reached */
		if(problem.IsGoal(current_node.first->state))
			return Solve(current_node.first);
		/* explore the current area */
		auto neighbors =
			boost::adjacent_vertices(current, *static_graph_.first);

		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
			string neighbor = ids_map[node_index[*n_it]];
			auto current_neigh = (*search_map)[neighbor];
			/* node not yet explored */
			if(current_neigh.first->color  ==  WHITE){
				/* mark the node as explored */
				current_neigh.first->color = BLACK;
				auto neigh_cost = current_node.second +
		   			(*static_graph)
		   			[boost::edge(current,*n_it,(*static_graph)).first] +
		   			(*dynamic_graph)
		   			[boost::edge(current,*n_it,(*dynamic_graph)).first];
		   		current_neigh.first->parent = current_node.first;
		   		current_neigh.second = neigh_cost;
		   		contour->push(current_neigh);
			}
		}
	}
	/* search failed */
	return EMPTY;
}