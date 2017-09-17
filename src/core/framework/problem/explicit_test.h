/**
 * @file
 * @brief Test which simply compares two states.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef EXPLICIT_TEST_H
#define EXPLICIT_TEST_H

#include "goal_test.h"

namespace path_finder
{

template <typename State> class ExplicitTest;

template <typename State>
class ExplicitTest : public GoalTest<State>
{
   public:
      bool Test(State, State)
      const noexcept;
};

/* import template implementation */
#include "explicit_test.cpp"
}
#endif /*EXPLICIT_TEST_H*/