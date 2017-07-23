using std::priority_queue;
using std::vector;

template <typename State>
priority_queue<
	std::pair<NodeColored<State>*, uint>,
	vector<std::pair<NodeColored<State>*, uint>>,
	NodeComparator<State, uint>
	>*
ColoredSearchQueueMaker<State>::MakeQueue() const noexcept
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;

	return new priority_queue<SearchableColoredNode,
							vector<SearchableColoredNode>,
							NodeComparator<State, uint>>();
}

template <typename State>
std::function<
			void
			(priority_queue<
				std::pair<NodeColored<State>*, uint>,
				vector<std::pair<NodeColored<State>*, uint>>,
				NodeComparator<State, uint>
				>*)
			>
ColoredSearchQueueMaker<State>::MakeQueueDestructor(void) const noexcept
{
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;

	return [](priority_queue<SearchableColoredNode,
							vector<SearchableColoredNode>,
							NodeComparator<State, uint>> * queue)
			{
				const int size = queue->size();
				for(int i=0; i < size; ++i){
					auto element = queue->top();
					delete element.first;
					queue->pop();
				}
				delete queue;
			};
}