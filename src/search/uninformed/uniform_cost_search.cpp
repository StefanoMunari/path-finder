using std::priority_queue;
using std::map;
using std::vector;
using std::list;
using std::string;

template <typename State>
UniformCostSearch<State>::UniformCostSearch(GraphPtr_IdMap static_graph)
noexcept{
	this->_static_graph = static_graph;
	this->_qmaker = ColoredQueueMaker<State>();
	this->_search_map_maker = ColoredSearchMapMaker<State>();
}

template <typename State>
list<State>*
UniformCostSearch<State>::Solve(Node<State>* last){
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
UniformCostSearch<State>::Search(GraphPtr_IdMap dynamic_graph_,
	const Problem<State>& problem){
	/* shortcut for verbose type */
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;
	/* boost-property accessors */
	IndexMap node_index =
		boost::get(boost::vertex_index, (*_static_graph.first));
	/* variables */
	Graph *static_graph = _static_graph.first;
	Graph *dynamic_graph = dynamic_graph_.first;
	map<string, int>* indexes_map = (map<string, int>*)_static_graph.second;
	auto ids_map = Algorithm::GetReversedMap<string, int>(indexes_map);
	auto contour = this->_qmaker.MakeQueue(problem.GetFirstState());
	auto search_map =
		this->_search_map_maker.MakeSearchMap(
			(contour->top()).first->state, &ids_map, _static_graph.first);
	VertexDescriptor current, end;
	end = boost::graph_traits<Graph>::null_vertex();

	/* body */
	while(!contour->empty() && (current != end)){
		auto current_node = contour->top();
		contour->pop();
		current = (*indexes_map)[current_node.first->state];
		/* goal reached - search completed*/
		if(problem.IsGoal(current_node.first->state))
			return Solve(current_node.first);
		/* explore the current area */
		current_node.first->color = BLACK;
		auto neighbors =
			boost::adjacent_vertices(current, *_static_graph.first);

		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
			string neighbor = ids_map[node_index[*n_it]];
			auto current_neigh = (*search_map)[neighbor];
			auto neigh_cost = current_node.second +
					(*static_graph)
					[boost::edge(current,*n_it,(*static_graph)).first] +
					(*dynamic_graph)
					[boost::edge(current,*n_it,(*dynamic_graph)).first];
			if(current_neigh.first->color  ==  WHITE){
				current_neigh.first->color = GRAY;
		   		current_neigh.first->parent = current_node.first;
		   		current_neigh.second = neigh_cost;
		   		contour->push(current_neigh);
			}
			else if((current_neigh.first->color == GRAY) &&
					(current_neigh.second > neigh_cost)){
				current_neigh.first->parent = current_node.first;
				current_neigh.second = neigh_cost;
			}
		}
	}
	/* search failed */
	return EMPTY;
}