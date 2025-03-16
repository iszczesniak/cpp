#include <iostream>
#include <utility>

struct A
{
  void foo() &
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void foo() &&
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int
main()
{
  A a;
  a.foo();
  A().foo();
}
