using std::priority_queue;
using std::queue;
using std::vector;

template <typename State>
priority_queue<
	std::pair<NodeColored<State>*, NodeCosts *>,
	vector<std::pair<NodeColored<State>*, NodeCosts *>>,
	NodeComparator<State, NodeCosts>
	>*
ColoredInformedQueueMaker<State>::MakePriorityQueue(void) const noexcept
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, NodeCosts *> InformedColoredNode;

	return new priority_queue<InformedColoredNode, vector<InformedColoredNode>,
		NodeComparator<State, NodeCosts>>();;
}

template <typename State>
std::queue<
	std::pair<NodeColored<State>*,  NodeCosts *>>*
ColoredInformedQueueMaker<State>::MakeQueue(void) const noexcept
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, NodeCosts *> InformedColoredNode;

	return new queue<InformedColoredNode>();;
}

template <typename State>
std::function<
	void
	(priority_queue<
		std::pair<NodeColored<State>*,  NodeCosts *>,
		std::vector<std::pair<NodeColored<State>*,  NodeCosts *>>,
		NodeComparator<State, NodeCosts>
		>*)
	>
ColoredInformedQueueMaker<State>::MakePriorityQueueDestructor(void)
const noexcept
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, NodeCosts *> InformedColoredNode;

	return [](priority_queue<
				InformedColoredNode,
				vector<InformedColoredNode>,
				NodeComparator<State, NodeCosts>> * queue)
			{
				const int size = queue->size();
				for(int i=0; i < size; ++i){
					auto pair = queue->top();
					queue->pop();
					delete pair.first;
					delete pair.second;
				}
				delete queue;
			};
}

template <typename State>
std::function<
	void
	(queue<
		std::pair<NodeColored<State>*,  NodeCosts *>>*)
	>
ColoredInformedQueueMaker<State>::MakeQueueDestructor(void)
const noexcept
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, NodeCosts *> InformedColoredNode;

	return [](queue<
				InformedColoredNode> * queue)
			{
				const int size = queue->size();
				for(int i=0; i < size; ++i){
					auto pair = queue->front();
					queue->pop();
					delete pair.first;
					delete pair.second;
				}
				delete queue;
			};
}