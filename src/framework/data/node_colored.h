#ifndef NODE_COLORED_H
#define NODE_COLORED_H

#include "node.h"
#include "../../utils/node_color.h"

namespace path_finder
{
	template <typename State>
	class NodeColored : public Node<State>{
	  public:
	  	NodeColored(State state, NodeColored* parent, Color color) noexcept;
	  	Color color;
	};

  NodeColored::NodeColored(State state, NodeColored* parent, Color color)
  noexcept : Node(state, cost, parent){
  	this->color=color;
  };
}
#endif /*NODE_COLORED_H*/