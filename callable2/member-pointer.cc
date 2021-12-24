#include <iostream>

void
foo()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

struct A
{
  void (*p)();
};

int
main()
{
  A a;
  a.p = foo;
  (*a.p)();
  a.p();
}
