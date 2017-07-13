using std::priority_queue;
using std::map;
using std::vector;
using std::list;
using std::string;
using std::shared_ptr;

template <typename State>
AStarSearch<State>::AStarSearch() noexcept
{
	this->_qmaker = ColoredQueueMaker<State>();
	this->_search_map_maker = ColoredInformedMapMaker<State>();
	this->_heuristic = ExactHeuristic<State>();
}

template <typename State>
AStarSearch<State>::AStarSearch(const AStarSearch& that){
	this->_qmaker = that._qmaker;
	this->_search_map_maker = that._search_map_maker;
	this->_heuristic = that._heuristic;
}

template <typename State>
AStarSearch<State>&
AStarSearch<State>::operator=(const AStarSearch& that){
	this->_qmaker = that._qmaker;
	this->_search_map_maker = that._search_map_maker;
	this->_heuristic = that._heuristic;
	return *this;
}

template <typename State>
list<State>*
AStarSearch<State>::Solve(Node<State>* last){
	Node<State>* iterator = last;
	list<State>* result = new list<State>();
	while(iterator){
		result->push_front(iterator->state);
		iterator = iterator->parent;
	}
	return result;
}

template <typename State>
list<State>*
AStarSearch<State>::Search(GraphPtr_IdMap static_graph_,
	shared_ptr<GraphPtr_IdMap> dynamic_graph_,
	const Problem<State>& problem)
{
	/* boost-property accessors */
	IndexMap node_index =
		boost::get(boost::vertex_index, (*static_graph_.first));
	/* define variables */
	Graph *static_graph = static_graph_.first;
	Graph *dynamic_graph = (dynamic_graph_.get())->first;
	map<string, int>* indexes_map = (map<string, int>*)static_graph_.second;
	auto ids_map = Algorithm::GetReversedMap<string, int>(indexes_map);
	auto contour = this->_qmaker.MakeQueue(problem.GetFirstState());
	auto search_map =
		this->_search_map_maker.MakeInformedMap(&ids_map, static_graph);
	/* TODO */
	/* search failed */
	return EMPTY;
}