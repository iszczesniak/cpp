#include <functional>
#include <iostream>

struct A
{
  void foo() &
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  void foo() &&
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
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
}
