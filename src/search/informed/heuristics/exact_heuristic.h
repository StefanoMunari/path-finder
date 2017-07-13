/**
 * @file
 * @brief Interface for the solver.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef HEURISTIC_FUNCTION_H
#define HEURISTIC_FUNCTION_H

#include "../framework/data/node.h"
#include <list>

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class HeuristicFunction;

	/**
	 * @brief Computes an exact cost heuristic based on the info available.
	*/
	template <typename State>
	class ExactHeuristic
	: public HeuristicFunction<State> {

		public:
			/**
			 * Computes the estimated value from the goal for each edge of
			 * the map.
			 *
			 * @param graph_map - the map which contains all default costs
			 *					  (UINT_MAX) which HeuristicFunction estimates
			 * @param goal - the goal node
			 * @return the informed graph - it contains a
			 *			map in the following format:
			 *				key -> [<key, cost>, <key, cost>, ...]
			 *			where each key is a Vertex_Id; each <key, cost>
			 *			represents an edge where the cost is the estimated cost
			 *			calculated by the heuristic function. It is similar to
			 *			an adjacency list but with access in O(1).
			 */
			virtual
			std::map<NodeColored<State> *,
				list<pair<NodeColored<State> *, uint>>> *
				Eval(std::map<NodeColored<State> *,
						list<pair<NodeColored<State> *, uint>>> *,
					NodeColored<State> *) =0;
	};
}
#endif /*HEURISTIC_FUNCTION_H*/