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
	  	Node* parent;
	};

  template <typename State>
  Node<State>::Node(State state, Node* parent) noexcept
  : state(state), parent(parent) {};
}
#endif /*NODE_H*/