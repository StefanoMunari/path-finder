/**
 * @file
 * @brief Interface for the solver.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef EXACT_HEURISTIC_H
#define EXACT_HEURISTIC_H

#include "heuristic_function.h"
#include "../../../framework/data/factory/colored_informed_queue_maker.h"
#include "../../../framework/data/utils/node_color.h"
#include "../../../utils/types.h"

namespace path_finder
{

template <typename State> class HeuristicFunction;

/**
 * @brief Computes an exact cost heuristic based on the available info.
*/
template <typename State>
class ExactHeuristic
: public HeuristicFunction<State>
{

	public:
		ExactHeuristic() noexcept {};
		ExactHeuristic(const ExactHeuristic&) noexcept {};
		ExactHeuristic& operator=(const ExactHeuristic&) noexcept {};
		~ExactHeuristic() noexcept {};
		/**
		 * Computes the estimated value from the goal for each edge of
		 * the map. It is computed based on the exact static cost of each
		 * node, the tree is traversed considering the goal node as
		 * root and keeping the cheapest path as better estimated cost each
		 * time there are multiple estimated costs for a node. It uses a priority
		 * queue of colored nodes. So, each node is explored only one time.
		 * The time complexity is O(branching*number_of_nodes).
		 *
		 * @pre the cost of each edge of the graph parameter is symmetric.
		 *		i.e. cost(A -> B) == cost(B -> A) == 10
		 *
		 * @post all nodes->color are BLACK (completely visited)
		 *
		 * @param informed_map the map to be updated with the estimated costs
		 * @param graph the graph of static costs
		 * @param indexes_map given a node identifiers it return the node index
		 * @param ids_map given a node index it returns the node identifier
		 * @param goal the goal state
		 * @return informed_map the graph with the estimated costs for each
		 * colored node.
		 */
		std::map<State,
				std::pair<NodeColored<State> *, NodeCosts *>> *
		Eval(
			std::map<State,
					std::pair<NodeColored<State> *, NodeCosts *>> *,
			Graph *,
			std::map<State, int> * const,
			std::map<int, State>&,
			State)
		const noexcept;
};

// import template implementation
#include "exact_heuristic.cpp"

}
#endif /*EXACT_HEURISTIC_H*/