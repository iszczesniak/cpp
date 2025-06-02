#include "myinvoke.hpp"

#include <iostream>

void foo()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void goo(int)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

struct A
{
  void foo()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void goo(int)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int
main()
{
  A a;

  myinvoke(foo);
  myinvoke(goo, 1);
  myinvoke([]{});
  myinvoke(&A::foo, a);
  myinvoke(&A::goo, a, 1);
}
