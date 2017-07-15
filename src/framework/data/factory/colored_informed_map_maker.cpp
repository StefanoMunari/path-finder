using std::map;

template <typename State>
map<State, std::pair<NodeColored<State> *,NodeCosts *>> *
ColoredInformedMapMaker<State>::MakeMap(
	map<string, std::pair<NodeColored<State> *, uint>> * search_map)
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State> *,NodeCosts *> InformedColoredNode;

	auto informed_map = new map<State, InformedColoredNode>();

	// convert the search_map into an informed_map
	for(auto const& element : (*search_map))
	{
		string s = element.first;
		InformedColoredNode n =
			InformedColoredNode(element.second.first, new NodeCosts);
		informed_map->insert(std::pair<State, InformedColoredNode>(s, n));
	}

	return informed_map;
}

template <typename State>
std::function<
			void
			(std::map<State,
					std::pair<NodeColored<State> *,NodeCosts *>> *)
			>
ColoredInformedMapMaker<State>::MakeMapDestructor(void)
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State> *,NodeCosts *> InformedColoredNode;

	return [](map<State, InformedColoredNode> * informed_map)
			{
				for(auto & element : (*informed_map))
				{
					delete element.second.first;
					delete element.second.second;
				}
			};
}