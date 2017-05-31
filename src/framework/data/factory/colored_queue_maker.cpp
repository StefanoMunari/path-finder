using std::priority_queue;
using std::vector;

template <typename State>
priority_queue<
	std::pair<NodeColored<State>*, uint>,
	vector<std::pair<NodeColored<State>*, uint>>,
	NodeComparator<State, uint>
	>*
ColoredQueueMaker<State>::MakeQueue(State source_id) {
	/* shortcut for verbose type */
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;
	/* declare local vars */
	auto source_node =
		SearchableColoredNode(
			new NodeColored<State>(source_id, nullptr, BLACK), 0);
	/* create the colored queue */
	auto coloreq_queue =
		new priority_queue<SearchableColoredNode, vector<SearchableColoredNode>,
		NodeComparator<State, uint>>();
	coloreq_queue->push(source_node);
	return coloreq_queue;
}