#include <iostream>
#include <utility>

template<typename G>
void f(G &&g)
{
  std::forward<G>(g)();
  // g();
}

struct A
{
  void
  operator()() &
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void
  operator()() &&
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int
main()
{
  f(A());
  A a;
  f(a);
}
