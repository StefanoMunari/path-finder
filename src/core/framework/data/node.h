#ifndef NODE_H
#define NODE_H

namespace path_finder
{

template <typename State> class Node;

template <typename State>
class Node{
  public:
  	Node(State state, Node* parent) noexcept;
  	State state;
  	Node * parent;
};
// import template implementation
#include "node.cpp"

}
#endif /*NODE_H*/