template <typename State>
GreedySearch<State>::GreedySearch(GraphPtr_IdMap static_graph) noexcept{
	this->_static_graph = static_graph;
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
GreedySearch<State>::Search(GraphPtr_IdMap dynamic_graph_,
	const Problem<State>& problem){

	/* Boost-property accessors */
	IndexMap node_index =
		boost::get(boost::vertex_index, (*_static_graph.first));
	/* Variables */
	Graph *static_graph = _static_graph.first;
	Graph *dynamic_graph = dynamic_graph_.first;
	map<string, int>* indexes_map = (map<string, int>*)_static_graph.second;
	auto ids_map = Algorithm::GetReversedMap<string, int>(indexes_map);
	auto contour = this->_MakeQueue(problem.GetFirstState());
	auto search_map = this->_MakeSearchMap(
		(contour->top()).first->state, &ids_map);
	VertexDescriptor current, end;
	end = boost::graph_traits<Graph>::null_vertex();

	/* Body */
	while(!contour->empty() && (current != end)){
		auto current_node = contour->top();
		contour->pop();
		current = (*indexes_map)[current_node.first->state];
		/* goal reached */
		if(problem.IsGoal(current_node.first->state))
			return Solve(current_node.first);
		/* explore the current area */
		auto neighbors = boost::adjacent_vertices(current, *_static_graph.first);

		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
			string neighbor = ids_map[node_index[*n_it]];
			auto current_neigh = (*search_map)[neighbor];
			if(current_neigh.first->color  ==  WHITE){
				current_neigh.first->color = BLACK;
				auto neigh_cost = current_node.second +
		   			(*static_graph)[boost::edge(current,*n_it,(*static_graph)).first] +
		   			(*dynamic_graph)[boost::edge(current,*n_it,(*dynamic_graph)).first];
		   		current_neigh.first->parent = current_node.first;
		   		current_neigh.second = neigh_cost;
		   		contour->push(current_neigh);
			}
		}
	}
	/* search failed */
	return nullptr;
}

template <typename State>
priority_queue<
	std::pair<NodeColored<State>*, uint>,
	vector<std::pair<NodeColored<State>*, uint>>,
	NodeComparator<State, uint>
	>*
GreedySearch<State>::_MakeQueue(State source_id) {
	/* shortcut for verbose type */
	typedef std::pair<NodeColored<State>*, uint> SearchableTreeNode;
	/* declare local vars */
	auto source_node =
		SearchableTreeNode(
			new NodeColored<State>(source_id, nullptr, BLACK), 0);
	auto contour =
		new priority_queue<SearchableTreeNode, vector<SearchableTreeNode>,
		NodeComparator<State, uint>>();
	contour->push(source_node);
	return contour;
}

template <typename State>
map<string, std::pair<NodeColored<State>*, uint>>*
GreedySearch<State>::_MakeSearchMap(State source,
	map<int, string>* ids_map)
{
	/* Boost-property accessors */
	IndexMap node_index =
		boost::get(boost::vertex_index, (*(_static_graph.first)));
	/* shortcut for verbose type */
	typedef std::pair<NodeColored<State>*, uint> SearchableTreeNode;
	/* vars */
	auto search_map = new map<string, SearchableTreeNode>();
	auto vertexes = boost::vertices((*(_static_graph.first)));
	/* body */
	search_map->insert(
			std::pair<string, SearchableTreeNode>(
				source,
				SearchableTreeNode(
					new NodeColored<State>(source, nullptr, BLACK),0)));
	for(auto v_it = vertexes.first; v_it !=  vertexes.second; ++v_it)
		search_map->insert(
			std::pair<string, SearchableTreeNode>(
				(*ids_map)[node_index[*v_it]],
				SearchableTreeNode(
					new NodeColored<State>(
						(*ids_map)[node_index[*v_it]], nullptr, WHITE),
						UINT_MAX)));
	return search_map;
}