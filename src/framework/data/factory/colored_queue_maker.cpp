using std::priority_queue;
using std::vector;

template <typename State>
priority_queue<
	std::pair<NodeColored<State>*, uint>,
	vector<std::pair<NodeColored<State>*, uint>>,
	NodeComparator<State, uint>
	>*
ColoredQueueMaker<State>::MakeQueue() {
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;

	return new priority_queue<SearchableColoredNode,
							vector<SearchableColoredNode>,
							NodeComparator<State, uint>>();
}