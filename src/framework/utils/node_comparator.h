#ifndef NODE_COMPARATOR_H
#define NODE_COMPARATOR_H

#include "../data/node.h"
#include <utility>// std::pair

template <typename State, typename Num>
typedef struct NodeComparator
{
    bool operator()(const std::pair<Node<State>*, Num>& n1,
      const std::pair<Node<State>*, Num>& n2) const
    {
        return n1.second < n2.second;
    }
} NodeComparator;

#endif /*NODE_COMPARATOR_H*/