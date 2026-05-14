#include <functional>
#include <iostream>

struct A
{
  void foo() &
  {
  }

  void foo() &&
  {
  }
};

int
main()
{
  A a;
  a.foo();
  A().foo();

  // std::invoke(&A::foo, a);
  // std::invoke(&A::foo, A());

  // std::apply(&A::foo, std::forward_as_tuple(a));
  // std::apply(&A::foo, std::forward_as_tuple(A()));
}
