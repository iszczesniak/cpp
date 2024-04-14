#include <iostream>
#include <functional>
#include <string>

using namespace std;

template <typename G, typename ... Args>
decltype(auto)
f(G &&g, Args &&... args)
{
  cout << __PRETTY_FUNCTION__ << '\n';
  return std::invoke(std::forward<G>(g), std::forward<Args>(args)...);
}

void
foo()
{
  cout << __PRETTY_FUNCTION__ << '\n';
}

template <typename T>
void
goo(T)
{
  cout << __PRETTY_FUNCTION__ << '\n';
}

struct A
{
  void foo()
  {
    cout << __PRETTY_FUNCTION__ << '\n';
  }

  template <typename T>
  void goo(T)
  {
    cout << __PRETTY_FUNCTION__ << '\n';
  }
};

int
main()
{
  A a;

  f(foo);
  f(goo<int>, 1);
  f(&A::foo, a);
  f(&A::goo<int>, A(), 1);
}
