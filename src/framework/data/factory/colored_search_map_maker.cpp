using std::map;
using std::string;

template <typename State>
map<string, std::pair<NodeColored<State> *, uint>> *
ColoredSearchMapMaker<State>::MakeSearchMap(State source,
	map<int, string> * ids_map, Graph * graph)
{
	/* shortcut for verbose type */
	typedef std::pair<NodeColored<State>*, uint> SearchableTreeNode;
	/* Boost-property accessors */
	IndexMap node_index =
		boost::get(boost::vertex_index,*graph);
	/* vars */
	auto search_map = new map<string, SearchableTreeNode>();
	auto vertexes = boost::vertices(*graph);
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