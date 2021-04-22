#include <iostream>

void
foo()
{
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
}
