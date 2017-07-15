using std::map;
using std::string;

template <typename State>
map<string, std::pair<NodeColored<State>*, uint>> *
ColoredSearchMapMaker<State>::MakeMap(
	map<int, string> * ids_map, Graph * graph)
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;

	// Boost-property accessors
	IndexMap node_index =
		boost::get(boost::vertex_index,*graph);
	// vars
	auto search_map = new map<string, SearchableColoredNode>();
	auto vertexes = boost::vertices(*graph);
	// body
	for(auto v_it = vertexes.first; v_it !=  vertexes.second; ++v_it){
		string s = (*ids_map)[node_index[*v_it]];
		SearchableColoredNode n =
			SearchableColoredNode(
						new NodeColored<State>(
							(*ids_map)[node_index[*v_it]], nullptr, WHITE),
							UINT_MAX);
		search_map->insert(std::pair<string, SearchableColoredNode>(s,n));
	}

	return search_map;
}

template <typename State>
std::function<
			void
			(std::map<std::string, std::pair<NodeColored<State>*, uint>> *)
			>
ColoredSearchMapMaker<State>::MakeMapDestructor(void)
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;

	return [](map<string, SearchableColoredNode> * search_map)
			{
				for(auto & element : (*search_map))
					delete element.second.first;
			};
}