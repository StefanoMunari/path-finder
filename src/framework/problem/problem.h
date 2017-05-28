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
      State GetGoalState() const;
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
  /* import template implementation */
  #include "problem.cpp"
}
#endif /*PROBLEM_H*/