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

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class HeuristicFunction;

	/**
	 * @brief Computes an exact cost heuristic based on the available info.
	*/
	template <typename State>
	class ExactHeuristic
	: public HeuristicFunction<State> {

		public:
			ExactHeuristic() noexcept {};
			ExactHeuristic(const ExactHeuristic&) {};
			ExactHeuristic& operator=(const ExactHeuristic&) {};
			~ExactHeuristic() noexcept {};
			/**
			 * Computes the estimated value from the goal for each edge of
			 * the map. It is computed based on the exact static cost of each
			 * node, the tree is traversed in BFS considering the goal node as
			 * root and keeping the cheapest path as better estimated cost each
			 * time there are multiple estimated costs for a node.
			 *
			 * @pre the cost of each edge of the graph parameter is symmetric.
			 *		i.e. cost(A -> B) == cost(B -> A) == 10
			 *
			 * @post all nodes->color are BLACK (has been completely visited)
			 */
			std::map<State,
					std::pair<NodeColored<State> *, NodeCosts *>> *
			Eval(
				std::map<State,
						std::pair<NodeColored<State> *, NodeCosts *>> *,
				Graph *,
				std::map<State, int> * const,
				std::map<int, State>&,
				State);
	};

	// import template implementation
	#include "exact_heuristic.cpp"
}
#endif /*EXACT_HEURISTIC_H*/