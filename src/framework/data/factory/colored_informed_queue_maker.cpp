using std::priority_queue;
using std::vector;

template <typename State>
priority_queue<
	std::pair<NodeColored<State>*, NodeCosts *>,
	vector<std::pair<NodeColored<State>*, NodeCosts *>>,
	NodeComparator<State, NodeCosts>
	>*
ColoredInformedQueueMaker<State>::MakeQueue()
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, NodeCosts *> InformedColoredNode;

	return new priority_queue<InformedColoredNode, vector<InformedColoredNode>,
		NodeComparator<State, NodeCosts>>();;
}