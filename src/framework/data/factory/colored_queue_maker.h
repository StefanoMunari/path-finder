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
#include "../../utils/node_comparator.h"
#include <queue>
#include <vector>
#include <utility>// std::pair

typedef unsigned int uint;

namespace path_finder
{
	template <typename State> class ColoredQueueMaker;

	template <typename State>
	class ColoredQueueMaker {
	  public:
		std::priority_queue<
			std::pair<NodeColored<State>*, uint>,
			std::vector<std::pair<NodeColored<State>*, uint>>,
			NodeComparator<State, uint>>*
		MakeQueue(State);
	};

	/* import template implementation */
	#include "colored_queue_maker.cpp"
}
#endif /*COLORED_QUEUE_MAKER_H*/