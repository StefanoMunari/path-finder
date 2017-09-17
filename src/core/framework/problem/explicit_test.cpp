template <typename State>
bool
ExplicitTest<State>::Test(State x, State y) const noexcept
{
   return x == y;
}