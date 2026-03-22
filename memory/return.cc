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

  A a = foo();
  a.hello();
}
