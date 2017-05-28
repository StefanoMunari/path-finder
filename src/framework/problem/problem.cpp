template <typename State>
Problem<State>::Problem(const State& source, const State& goal) noexcept
: _source(source), _goal(goal) {};
/*
template <typename State>
Problem<State>::Problem(Problem && problem) noexcept
: _source(problem._source), _goal(problem._goal) {};
*/
template <typename State>
Problem<State>::~Problem() noexcept {};
/*
template <typename State>
Problem<State>::Problem(Problem && problem) noexcept{
  this->~Problem();
  this->Problem(problem);
  return *this;
};
*/
template <typename State>
State Problem<State>::GetFirstState() const {
  return _source;
};

template <typename State>
State Problem<State>::GetGoalState() const {
  return _goal;
};

template <typename State>
bool Problem<State>::IsGoal(const State& state) const{
  return (state  ==  _goal);
}
/*
template <typename State>
GoalTest<State>* Problem<State>::getGoalTest() const {
  return test_;
};

template <typename State>
ActionFunction* Problem<State>::getActionFunction() const {
  return action_function_;
};
*/