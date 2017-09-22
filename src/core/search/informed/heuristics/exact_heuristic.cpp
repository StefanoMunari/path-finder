using std::map;
using std::string;

template <typename State>
std::map<State, std::pair<NodeColored<State> *, NodeCosts *>> *
ExactHeuristic<State>::Eval(
	map<State, std::pair<NodeColored<State> *, NodeCosts *>> * informed_map,
	Graph * graph,
	map<State, int> * const indexes_map,
	map<int, State>& ids_map,
	State goal)
const noexcept
{
	// boost-property accessors
	IndexMap node_index =
		boost::get(boost::vertex_index, (*graph));
	// create a factory of colored informed queues
	ColoredInformedQueueMaker<State> qmaker =
		ColoredInformedQueueMaker<State>();
	// the contour is a priority colored informed queue
	auto contour = qmaker.MakeQueue();
	{
		// the estimated cost for the goal node is zero
		auto goal_node = (*informed_map)[goal];
		goal_node.second->h = 0;
		// insert the goal as the first node of the priority queue
		contour->push(goal_node);
	}
	// declare graph iterators
	VertexDescriptor current, end;
	end = boost::graph_traits<Graph>::null_vertex();

	while(!contour->empty() && (current != end))
	{
		// get the colored informed node
		auto current_node = contour->front();
		contour->pop();

		// get the related boost::vertex_descriptor
		current = (*indexes_map)[current_node.first->state];

		// get the set of neighbors using the vertex descriptor
		auto neighbors =
			boost::adjacent_vertices(current, (*graph));
		// update the estimated costs for the neighbors
		for(auto n_it = neighbors.first; n_it !=  neighbors.second; ++n_it)
		{
			// get the neighbor name/state
			State neighbor = ids_map[node_index[*n_it]];
			// get the neighbor node (pointer)
			auto current_neigh = (*informed_map)[neighbor];
			// compute the estimated cost
			auto estimated_neigh_cost =
					current_node.second->h +
					(*graph)[boost::edge(current,*n_it,(*graph)).first];

			// neighbor not yet explored or completed
			if(current_neigh.first->color  ==  WHITE)
			{
				// mark as explored
				current_neigh.first->color = GRAY;
				// update the estimated cost for this neighbor
				current_neigh.second->h = estimated_neigh_cost;
				// add it to the priority queue
				contour->push(current_neigh);
			}
			// neighbor has been explored and
			// has an higher estimated cost than the current one
			else if((current_neigh.first->color == GRAY) &&
					(current_neigh.second->h > estimated_neigh_cost))
			{
				current_neigh.second->h = estimated_neigh_cost;
			}
		}
		// mark node as completed
		current_node.first->color = BLACK;
	}

	(qmaker.MakeQueueDestructor())(contour);

	return informed_map;
}