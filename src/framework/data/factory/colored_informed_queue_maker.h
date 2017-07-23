/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#ifndef COLORED_INFORMED_QUEUE_MAKER_H
#define COLORED_INFORMED_QUEUE_MAKER_H

#include "../node.h"
#include "../utils/node_comparator.h"
#include <queue>
#include <vector>
#include <utility>// std::pair
#include <functional>// std::function

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class ColoredInformedQueueMaker;


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
	class ColoredInformedQueueMaker{
	  public:
		std::priority_queue<
			std::pair<NodeColored<State>*,  NodeCosts *>,
			std::vector<std::pair<NodeColored<State>*,  NodeCosts *>>,
			NodeComparator<State, NodeCosts>>*
		MakeQueue();
		std::function<
			void
			(std::priority_queue<
				std::pair<NodeColored<State>*,  NodeCosts *>,
				std::vector<std::pair<NodeColored<State>*,  NodeCosts *>>,
				NodeComparator<State, NodeCosts>
				>*)
			>
		MakeQueueDestructor(void);
	};

	// import template implementation
	#include "colored_informed_queue_maker.cpp"
}
#endif /*COLORED_INFORMED_QUEUE_MAKER_H*/