template <typename State>
Problem<State>::Problem(const State& source, const State& goal,
  GoalTest<State>* test) noexcept
: _source(source), _goal(goal)
{
  _test = test;
};
/*
template <typename State>
Problem<State>::Problem(Problem && problem) noexcept
: _source(problem._source), _goal(problem._goal) {};
*/
template <typename State>
Problem<State>::~Problem() noexcept
{
  if(_test)
    delete _test;
};
/*
template <typename State>
Problem<State>::Problem(Problem && problem) noexcept{
  this->~Problem();
  this->Problem(problem);
  return *this;
};
*/
template <typename State>
State Problem<State>::GetFirstState() const
{
  return _source;
};

template <typename State>
State Problem<State>::GetGoalState() const
{
  return _goal;
};

template <typename State>
bool Problem<State>::IsGoal(const State& state) const
{
  if(_test)
    return _test->Test(state, _goal);
  return false;
}

/*
template <typename State>
ActionFunction* Problem<State>::getActionFunction() const {
  return action_function_;
};
*/