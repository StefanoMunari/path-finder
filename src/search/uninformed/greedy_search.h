/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
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

	template <typename State>
	class GreedySearch
	: public Searchable<State>, public Solvable<State> {

		public:
			GreedySearch(GraphPtr_IdMap static_graph) noexcept;
			std::list<State>* Solve(Node<State>*);
			std::list<State>* Search(GraphPtr_IdMap, const Problem<State>&);

		private:
			GraphPtr_IdMap _static_graph;
			ColoredQueueMaker<State> _qmaker;
			ColoredSearchMapMaker<State> _search_map_maker;
	};

	/* import template implementation */
	#include "greedy_search.cpp"
}
#endif /*GREEDY_SEARCH_H*/