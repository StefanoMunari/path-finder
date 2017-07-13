/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef COLORED_QUEUE_MAKER_H
#define COLORED_QUEUE_MAKER_H

#include "../node.h"
#include "../utils/node_comparator.h"
#include <queue>
#include <vector>
#include <utility>// std::pair

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class ColoredQueueMaker;


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
	class ColoredQueueMaker {
	  public:
		std::priority_queue<
			std::pair<NodeColored<State>*, uint>,
			std::vector<std::pair<NodeColored<State>*, uint>>,
			NodeComparator<State, uint>>*
		MakeQueue(State);
	};

	// import template implementation
	#include "colored_queue_maker.cpp"
}
#endif /*COLORED_QUEUE_MAKER_H*/