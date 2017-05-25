#ifndef NODE_COMPARATOR_H
#define NODE_COMPARATOR_H

#include "../data/node.h"
#include <utility>// std::pair

namespace path_finder
{
	template <typename State, typename Num> struct NodeComparator;

	template <typename State, typename Num>
	struct NodeComparator
	{
	    bool operator()(const std::pair<Node<State>*, Num>& n1,
	      const std::pair<Node<State>*, Num>& n2) const
	    {
	        return n1.second < n2.second;
	    }
	};
}
#endif /*NODE_COMPARATOR_H*/