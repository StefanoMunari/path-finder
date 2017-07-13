/**
 * @file
 * @brief  A* search on a graph.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef ASTAR_SEARCH_H
#define ASTAR_SEARCH_H

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
#include <memory>// std::shared_ptr
#include <utility>// std::pair
#include <algorithm>// std::for_each
#include <climits>// UINT_MAX

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class AStarSearch;

	/**
	 * @brief  A* search on a graph.
	*/
	template <typename State>
	class AStarSearch
	: public Searchable<State>, public Solvable<State> {

		public:
			/**
			 * @brief Class constructor - set ExactHeuristic as
			 *		  default heuristic
			 * @return an A* search algorithm
			*/
			AStarSearch() noexcept;
			AStarSearch(const AStarSearch&);
			AStarSearch& operator=(const AStarSearch&);
			~AStarSearch() noexcept {};
			void SetHeuristicFunction(HeuristicFunction *);
			std::list<State>* Solve(Node<State>*);
			std::list<State>* Search(GraphPtr_IdMap,
									std::shared_ptr<GraphPtr_IdMap>,
									const Problem<State>&);

		private:
			HeuristicFunction * _heuristic = nullptr;
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
	#include "astart_search.cpp"
}
#endif /*ASTAR_SEARCH_H*/