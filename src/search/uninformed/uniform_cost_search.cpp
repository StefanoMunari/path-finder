using std::priority_queue;
using std::map;
using std::vector;
using std::list;
using std::string;
using std::shared_ptr;

template <typename State>
UniformCostSearch<State>::UniformCostSearch() noexcept
{
	this->_qmaker = ColoredQueueMaker<State>();
	this->_search_map_maker = ColoredSearchMapMaker<State>();
}

template <typename State>
UniformCostSearch<State>::UniformCostSearch(const UniformCostSearch& that){
	this->_qmaker = that._qmaker;
	this->_search_map_maker = that._search_map_maker;
}

template <typename State>
UniformCostSearch<State>&
UniformCostSearch<State>::operator=(const UniformCostSearch& that){
	this->_qmaker = that._qmaker;
	this->_search_map_maker = that._search_map_maker;
	return *this;
}

template <typename State>
list<State>*
UniformCostSearch<State>::Solve(Node<State>* last){
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
UniformCostSearch<State>::Search(GraphPtr_IdMap static_graph_,
	shared_ptr<GraphPtr_IdMap> dynamic_graph_,
	const Problem<State>& problem)
{
	/* boost-property accessors */
	IndexMap node_index =
		boost::get(boost::vertex_index, (*static_graph_.first));
	// shortcut for verbose type
	typedef std::pair<NodeColored<State>*, uint> SearchableColoredNode;
	/* define variables */
	Graph *static_graph = static_graph_.first;
	Graph *dynamic_graph = (dynamic_graph_.get())->first;
	// the resulting path is empty (no solution found yet)
	list<State>* result = EMPTY;
	// state -> vertex_index
	map<string, int>* indexes_map = (map<string, int>*)static_graph_.second;
	// vertex_index -> state
	auto ids_map = Algorithm::GetReversedMap<string, int>(indexes_map);
	// set-up contour
	auto contour = this->_qmaker.MakeQueue();
	// push the source node and mark it as completed/explored
	contour->push(
		SearchableColoredNode(
			new NodeColored<State>(problem.GetFirstState(), nullptr, BLACK),
			0));
	auto search_map =
		this->_search_map_maker.MakeMap(&ids_map, static_graph_.first);
	// remove the deprecated source,
	// insert the source node marking it as BLACK (visited/completed)
	{
		auto deprecated_node = (*search_map)[problem.GetFirstState()];
		delete deprecated_node.first;
	}
	(*search_map)[problem.GetFirstState()] =
							SearchableColoredNode(
								new NodeColored<State>(
									problem.GetFirstState(), nullptr, BLACK),0);
	// declare iterators
	VertexDescriptor current, end;
	end = boost::graph_traits<Graph>::null_vertex();

	while(!contour->empty() && (current != end)){
		auto current_node = contour->top();
		contour->pop();
		current = (*indexes_map)[current_node.first->state];
		// goal reached - search completed
		if(problem.IsGoal(current_node.first->state)){
			result = Solve(current_node.first);
			break;
		}
		// explore the current area
		current_node.first->color = BLACK;
		auto neighbors =
			boost::adjacent_vertices(current, *static_graph_.first);

		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it){
			string neighbor = ids_map[node_index[*n_it]];
			auto current_neigh = (*search_map)[neighbor];
			auto neigh_cost = current_node.second +
					(*static_graph)
					[boost::edge(current,*n_it,(*static_graph)).first] +
					(*dynamic_graph)
					[boost::edge(current,*n_it,(*dynamic_graph)).first];
			// neighbor not yet explored
			if(current_neigh.first->color  ==  WHITE){
				current_neigh.first->color = GRAY;
		   		current_neigh.first->parent = current_node.first;
		   		current_neigh.second = neigh_cost;
		   		contour->push(current_neigh);
			}
			// neighbor has been explored and
			// has an higher cost than the current one
			else if((current_neigh.first->color == GRAY) &&
					(current_neigh.second > neigh_cost)){
				current_neigh.first->parent = current_node.first;
				current_neigh.second = neigh_cost;
			}
		}
	}

	(this->_search_map_maker.MakeMapDestructor())(search_map);
	return result;
}