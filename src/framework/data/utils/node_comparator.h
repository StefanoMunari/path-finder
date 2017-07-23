#ifndef NODE_COMPARATOR_H
#define NODE_COMPARATOR_H

#include "../node.h"
#include <utility>// std::pair

namespace path_finder
{

template <typename State, typename Num> struct NodeComparator;

/**
 * @brief  Compare two nodes - true if the value of the first is greater
 *			than the value of the second one, false otherwise.
 *
 * @param n1 - the first node
 * @param n2 - the second node
 *
 * @return the result of the comparison
*/
template <typename State, typename Num>
struct NodeComparator
{
	bool operator()(const std::pair<Node<State>*, Num *>& n1,
	  const std::pair<Node<State>*, Num *>& n2) const noexcept
	{
	    return *(n1.second) > *(n2.second);
	}

	bool operator()(const std::pair<Node<State>*, Num>& n1,
	  const std::pair<Node<State>*, Num>& n2) const noexcept
	{
	    return n1.second > n2.second;
	}
};

}
#endif /*NODE_COMPARATOR_H*/