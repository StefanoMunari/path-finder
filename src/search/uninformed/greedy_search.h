/**
 * @file
 * @brief  Greedy search on a graph.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef GREEDY_SEARCH_H
#define GREEDY_SEARCH_H

#include "../searchable.h"
#include "../solvable.h"
#include "../../framework/problem/problem.h"
#include "../../framework/data/node_colored.h"
#include "../../framework/data/factory/colored_queue_maker.h"
#include "../../framework/data/factory/colored_search_map_maker.h"
#include "../../utils/boost_types.h"
#include "../../utils/constants.h"
#include "../../utils/algorithm.h"
#include <queue>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <utility>// std::pair
#include <algorithm>// std::for_each
#include <climits>// UINT_MAX

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class GreedySearch;

	/**
	 * @brief  Greedy search on a graph.
	 *
	 * Local search which choose, for each edge of the graph, the less costly
	 * one avoiding cycles.
	 * It is both fast and unreliable. It can easily fall in a local minimum.
	 * Analysis:
	 * - Complete: FALSE. It can not exit from a blind alley.
	 *	It does not return on previous visited nodes to avoid cycles.
	 * - Optimal: FALSE. It always choose the best local path.
	 * - Time: O(depth)
	 * - Space: O(branching*max_state_space)
	*/
	template <typename State>
	class GreedySearch
	: public Searchable<State>, public Solvable<State> {

		public:
			/**
			 * @brief Class constructor
			 * @param static_graph - a pair which represents the static topology
			 *	with the associated static costs for each edge
			 * @return a greedy search algorithm
			*/
			GreedySearch() noexcept;
			std::list<State>* Solve(Node<State>*);
			std::list<State>* Search(GraphPtr_IdMap, GraphPtr_IdMap,
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
	#include "greedy_search.cpp"
}
#endif /*GREEDY_SEARCH_H*/