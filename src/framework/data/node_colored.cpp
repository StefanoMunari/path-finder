template <typename State>
NodeColored<State>::NodeColored(State state, NodeColored<State>* parent, NodeColor color)
noexcept : Node<State>(state, parent)
{
	this->color = color;
};