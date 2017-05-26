#ifndef PROBLEM_H
#define PROBLEM_H

namespace path_finder
{
  template <typename State> class Problem;

  template <typename State>
  class Problem {
    public:
      Problem(const State&, const State&) noexcept;
        //, GoalTest<State>*
      Problem(const Problem &)  =delete;
      /*
      Problem(Problem &&) noexcept;
      */
      ~Problem() noexcept;
      Problem& operator= (const Problem&)  =delete;
      Problem& operator= (Problem&&) noexcept;
      State GetFirstState() const;
      bool IsGoal(const State& state) const;
      /*
      GoalTest<State>* getGoalTest() const;
      ActionFunction* getActionFunction() const;
      CostFunction* getCostFunction() const;
      */

    private:
      State _source;
      State _goal;
      /*
      GoalTest<State>* test_ = nullptr;
      ActionFunction* action_function_ = nullptr;
      CostFunction* cost_function_;
      */
  };

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
}
#endif /*PROBLEM_H*/