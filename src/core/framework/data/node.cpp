template <typename State>
Node<State>::Node(State state, Node* parent) noexcept
: state(state), parent(parent) {};