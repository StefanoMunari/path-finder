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
#include "../../framework/utils/node_comparator.h"
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

using std::priority_queue;
using std::map;
using std::vector;
using std::list;
using std::string;

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class GreedySearch;

	template <typename State>
	class GreedySearch : public Searchable<State>, public Solvable<State> {
	/*, Expand {*/
	  public:
	    GreedySearch(GraphPtr_IdMap static_graph) noexcept;
		std::list<State>* Solve(Node<State>*);
	    list<State>* Search(GraphPtr_IdMap, const Problem<State>&);
	  private:
	  	/*
	    virtual std::vector<Node>* Expand(Node*);
	    */
		priority_queue<
			std::pair<NodeColored<State>*, uint>,
			vector<std::pair<NodeColored<State>*, uint>>,
			NodeComparator<State, uint>>*
		_MakeQueue(State);

		map<string, std::pair<NodeColored<State>*, uint>>*
		_MakeSearchMap(State, map<int, string>*);

	    GraphPtr_IdMap _static_graph;
	};

	/* import template implementation */
	#include "greedy_search.cpp"
}
#endif /*GREEDY_SEARCH_H*/