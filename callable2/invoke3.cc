#include <chrono>
#include <iostream>
#include <functional>
#include <string>

using namespace std;

template <typename G, typename ... Args>
auto
f(G &&g, Args &&... args)
{
  cout << __PRETTY_FUNCTION__ << '\n';
  std::invoke(std::forward<G>(g), std::forward<Args>(args)...);
}

void
g()
{
  cout << __PRETTY_FUNCTION__ << '\n';
}

template <typename T>
void
g(T)
{
  cout << __PRETTY_FUNCTION__ << '\n';
}

struct A
{
  void g() &
  {
    cout << __PRETTY_FUNCTION__ << '\n';
  }

  template <typename T>
  void g() &&
  {
    cout << __PRETTY_FUNCTION__ << '\n';
  }
};

int
main()
{
  A a;

  f(g);
  //  f(g<int>, 1);
  f(&A::g, a);
  f(&A::g<int>, a, 1);
}
