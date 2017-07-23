/**
 * @file
 * @brief Interface for the solver.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef HEURISTIC_FUNCTION_H
#define HEURISTIC_FUNCTION_H

#include "../../../framework/data/node_colored.h"
#include "../../../framework/data/utils/node_costs.h"
#include "../../../utils/boost_types.h"
#include "../../../utils/types.h"
#include <map>
#include <string>
#include <utility>// std::pair
#include <climits>// UINT_MAX

namespace path_finder
{

template <typename State> class HeuristicFunction;

/**
 * @brief Interface for the heuristic function.
*/
template <typename State>
class HeuristicFunction
{
	public:
		HeuristicFunction() noexcept {};
		virtual ~HeuristicFunction() noexcept {};
		/**
		 * Computes the estimated value for each node of the map starting
		 * from the node which contains the goal state.
		 *
		 * @param informed_map - the map which contains all default costs
		 *						which HeuristicFunction will update
		 * @param graph - the graph which contains all the connections
		 *				between the nodes of the topology
		 * @param indexes_map - contains the mapping between node names
		 *						(aka states of the informed_map)
		 *						and the vertex_indexes of the graph
		 * @param ids_map - contains the mapping between vertex_indexes
		 *					of the graph and the node names (aka states)
		 * @param goal - the goal state
		 *
		 * @return the informed_map updated -  the estimated costs are
		 *			updated (distance current_node -> goal).
		 */
		virtual
		std::map<std::string,
				std::pair<NodeColored<State> *, NodeCosts *>> *
		Eval(std::map<std::string,
					std::pair<NodeColored<State> *, NodeCosts *>> *,
			Graph *,
			std::map<std::string, int> * const,
			std::map<int, std::string>&,
			State)
		const noexcept =0;
};

}
#endif /*HEURISTIC_FUNCTION_H*/