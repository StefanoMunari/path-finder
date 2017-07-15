using std::map;

template <typename State>
map<State, std::pair<NodeColored<State>*, uint>> *
ColoredSearchMapMaker<State>::MakeMap(
	map<int, State> * ids_map, Graph * graph)
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;

	// Boost-property accessors
	IndexMap node_index =
		boost::get(boost::vertex_index,*graph);
	// vars
	auto search_map = new map<State, SearchableColoredNode>();
	auto vertexes = boost::vertices(*graph);
	// body
	for(auto v_it = vertexes.first; v_it !=  vertexes.second; ++v_it){
		State s = (*ids_map)[node_index[*v_it]];
		SearchableColoredNode n =
			SearchableColoredNode(
						new NodeColored<State>(
							(*ids_map)[node_index[*v_it]], nullptr, WHITE),
							UINT_MAX);
		search_map->insert(std::pair<State, SearchableColoredNode>(s,n));
	}

	return search_map;
}

template <typename State>
std::function<
			void
			(std::map<State, std::pair<NodeColored<State>*, uint>> *)
			>
ColoredSearchMapMaker<State>::MakeMapDestructor(void)
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;

	return [](map<State, SearchableColoredNode> * search_map)
			{
				for(auto & element : (*search_map))
					delete element.second.first;
			};
}