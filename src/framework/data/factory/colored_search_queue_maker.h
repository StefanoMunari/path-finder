/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef colored_search_queue_maker_H
#define colored_search_queue_maker_H

#include "../node.h"
#include "../utils/node_comparator.h"
#include "../../../utils/types.h"
#include <queue>
#include <vector>
#include <utility>// std::pair
#include <functional>// std::function

namespace path_finder
{

template <typename State> class ColoredSearchQueueMaker;


/**
 * @brief  Factory of a priority queue of colored nodes.
 *
 * Creates a priority queue initialized only with the NOT connected source
 * node, which is BLACK and costs 0 by default.
 *
 * @param source - the source node
 *
 * @return priority queue which stores pairs of <Colored_Node*, cost>
 *
 * @pre the graph has only NOT negative costs (the minimum is 0)
*/
template <typename State>
class ColoredSearchQueueMaker {
  public:
	std::priority_queue<
		std::pair<NodeColored<State>*, uint>,
		std::vector<std::pair<NodeColored<State>*, uint>>,
		NodeComparator<State, uint>> *
	MakeQueue() const noexcept;
	std::function<
		void
		(priority_queue<
			std::pair<NodeColored<State>*, uint>,
			vector<std::pair<NodeColored<State>*, uint>>,
			NodeComparator<State, uint>
			>*)
		>
	MakeQueueDestructor(void) const noexcept;
};

// import template implementation
#include "colored_search_queue_maker.cpp"

}
#endif /*colored_search_queue_maker_H*/