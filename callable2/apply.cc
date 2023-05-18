#include <iostream>
#include <functional>
#include <string>
#include <tuple>

using namespace std;

template <typename G, typename T, typename E>
void
f(G &&g, T &&t, E && e)
{
  cout << e << ": ";

  std::apply(std::forward<G>(g), std::forward<T>(t));
}

void
foo()
{
  cout << __PRETTY_FUNCTION__ << '\n';
}

template <typename T>
void
goo(T x)
{
  cout << __PRETTY_FUNCTION__ << '\n';
}

struct A
{
  void foo(int x)
  {
    cout << __PRETTY_FUNCTION__ << '\n';
  }

  void goo(int x)
  {
    cout << __PRETTY_FUNCTION__ << '\n';
  }
};

int
main()
{
  A a;

  f(foo, make_tuple(), "Hello");
  f(goo<int>, make_tuple(1), 3.14159);
  f(&A::foo, forward_as_tuple(a, 1), .1);
  f(&A::goo, forward_as_tuple(A(), 1), 1);
}
