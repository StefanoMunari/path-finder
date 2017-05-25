#ifndef NODE_COLORED_H
#define NODE_COLORED_H

#include "node.h"
#include "../utils/node_color.h"

namespace path_finder
{
	template <typename State>
	class NodeColored : public Node<State>{
	  public:
	  	NodeColored(State state, NodeColored<State>* parent, NodeColor color) noexcept;
	  	NodeColor color;
	};

	template <typename State>
	NodeColored<State>::NodeColored(State state, NodeColored<State>* parent, NodeColor color)
	noexcept : Node<State>(state, parent)
	{
		this->color=color;
	};
}
#endif /*NODE_COLORED_H*/