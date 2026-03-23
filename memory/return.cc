#include "A.hpp"

A foo()
{
  A a("foo");
  return a;
}

A & goo()
{
  static A a("goo");
  return a;
}

int main()
{
  foo().hello();
  goo().hello();

  A f = foo();
  f.hello();

  A g = goo();
  g.hello();
}
