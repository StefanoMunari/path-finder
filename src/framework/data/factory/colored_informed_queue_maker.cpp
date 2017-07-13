using std::priority_queue;
using std::vector;

template <typename State>
priority_queue<
	std::pair<NodeColored<State>*, NodeCosts *>,
	vector<std::pair<NodeColored<State>*, NodeCosts *>>,
	NodeComparator<State, NodeCosts *>
	>*
ColoredInformedQueueMaker<State>::MakeQueue(
	std::pair<NodeColored<State>*,  NodeCosts *> node)
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, NodeCosts *> InformedColoredNode;
	// create the colored queue
	auto colored_queue =
		new priority_queue<InformedColoredNode, vector<InformedColoredNode>,
		NodeComparator<State, NodeCosts *>>();

	colored_queue->push(node);

	return colored_queue;
}