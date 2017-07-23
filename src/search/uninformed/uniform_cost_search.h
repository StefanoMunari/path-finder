/**
 * @file
 * @brief  Uniform-cost search on a graph.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef UNIFORM_COST_SEARCH_H
#define UNIFORM_COST_SEARCH_H

#include "../searchable.h"
#include "../solvable.h"
#include "../../framework/problem/problem.h"
#include "../../framework/data/node_colored.h"
#include "../../framework/data/factory/colored_queue_maker.h"
#include "../../framework/data/factory/colored_search_map_maker.h"
#include "../../utils/algorithm.h"
#include "../../utils/boost_types.h"
#include "../../utils/constants.h"
#include "../../utils/synch.h"// mutex_graph
#include "../../utils/types.h"
#include <queue>
#include <map>
#include <vector>
#include <list>
#include <memory>// std::shared_ptr
#include <utility>// std::pair
#include <algorithm>// std::for_each
#include <climits>// UINT_MAX

namespace path_finder
{
	template <typename State> class UniformCostSearch;

	/**
	 * @brief  Uniform-cost search on a graph.
	 *
	 * @pre the branching factor of each node of the graph must be finite
	 * @pre the step cost of each edge of the graph must be >= 0
	 *
	 * Search for the optimal path on the graph.
	 * Analysis (assuming that pre-conditions hold):
	 * - Complete: TRUE
	 * - Optimal: TRUE
	 * - Time: O(braching^(1+round(optimal_cost/epsilon)))
	 * - Space: O(braching^(1+round(optimal_cost/epsilon)))
	*/
	template <typename State>
	class UniformCostSearch
	: public Searchable<State>, public Solvable<State> {

		public:
			/**
			 * @brief Class constructor
			 * @param static_graph - a pair which represents the static topology
			 *	with the associated static costs for each edge
			 * @return a uniform-cost search algorithm
			*/
			UniformCostSearch() noexcept;
			UniformCostSearch(const UniformCostSearch&);
			UniformCostSearch& operator=(const UniformCostSearch&);
			~UniformCostSearch() noexcept {};
			std::list<State>* Solve(Node<State>*);
			std::list<State>* Search(
							GraphPtr_IdMap,
							std::shared_ptr<GraphPtr_IdMap>,
							const Problem<State>&);

		private:
			/**
			 * @brief instance of a colored queue factory class
			 * @see colored_queue_maker.h
			*/
			ColoredQueueMaker<State> _qmaker;
			/**
			 * @brief instance of a colored search map factory class
			 * @see colored_search_map_maker.h
			*/
			ColoredSearchMapMaker<State> _search_map_maker;
	};

	/* import template implementation */
	#include "uniform_cost_search.cpp"
}
#endif /*UNIFORM_COST_SEARCH_H*/