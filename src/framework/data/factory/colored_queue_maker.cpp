using std::priority_queue;
using std::vector;

template <typename State>
priority_queue<
	std::pair<NodeColored<State>*, uint>,
	vector<std::pair<NodeColored<State>*, uint>>,
	NodeComparator<State, uint>
	>*
ColoredQueueMaker<State>::MakeQueue(State node_id) {
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;
	// declare local vars
	auto node =
		SearchableColoredNode(
			new NodeColored<State>(node_id, nullptr, BLACK), 0);
	// create the colored queue
	auto colored_queue =
		new priority_queue<SearchableColoredNode, vector<SearchableColoredNode>,
		NodeComparator<State, uint>>();
	colored_queue->push(node);
	return colored_queue;
}