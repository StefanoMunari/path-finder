using std::map;
using std::string;

template <typename State>
map<string, std::pair<NodeColored<State> *, NodeCosts *>> *
ColoredInformedMapMaker<State>::MakeInformedMap(
	map<string, std::pair<NodeColored<State> *, uint>> * search_map)
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State> *,NodeCosts *> InformedColoredNode;

	auto informed_map = new map<string, InformedColoredNode>();

	// convert the search_map into an informed_map
	for(auto const& element : (*search_map))
	{
		string s = element.first;
		InformedColoredNode p =
			InformedColoredNode(element.second.first, new NodeCosts);
		// set all node colors to WHITE by default for informed search
		// WHITE means NOT yet explored or completed
		p.first->color = WHITE;
		informed_map->insert(std::pair<string, InformedColoredNode>(s, p));
	}

	return informed_map;
}