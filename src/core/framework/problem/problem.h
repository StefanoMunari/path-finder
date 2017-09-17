#ifndef PROBLEM_H
#define PROBLEM_H

#include "goal_test.h"

namespace path_finder
{

template <typename State> class Problem;

template <typename State>
class Problem {
  public:
    Problem(const State&, const State&, GoalTest<State>*) noexcept;
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
    ActionFunction* getActionFunction() const;
    */

  private:
    State _source;
    State _goal;
    GoalTest<State>* _test = nullptr;
    /*
    ActionFunction* action_function_ = nullptr;
    */
};

// import template implementation
#include "problem.cpp"

}
#endif /*PROBLEM_H*/