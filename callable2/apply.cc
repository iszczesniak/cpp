#include <iostream>
#include <functional>
#include <string>
#include <tuple>

using namespace std;

template <typename G, typename T, typename E>
void
f(G &&g, T &&t, const E &e)
{
  cout << __PRETTY_FUNCTION__ << ": " << e << '\n';
  std::apply(std::forward<G>(g), std::forward<T>(t));
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

  f(foo, make_tuple(), "Hello");
  f(goo<int>, make_tuple(1), 3.14159);
  f(&A::foo, forward_as_tuple(a), .1);
  f(&A::goo<int>, forward_as_tuple(A(), 1), 1);
}
