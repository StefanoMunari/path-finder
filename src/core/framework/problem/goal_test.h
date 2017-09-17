/**
 * @file
 * @brief Interface for the goal test.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef GOAL_TEST_H
#define GOAL_TEST_H

namespace path_finder
{

template <typename State> class GoalTest;

/**
* @brief Interface for the goal test.
*/
template <typename State>
class GoalTest{
  public:
    virtual
    bool Test(State, State)
    const noexcept =0;
    virtual
    ~GoalTest() noexcept {};
};

}
#endif /*GOAL_TEST_H*/