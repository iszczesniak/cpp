#include "A.hpp"

#include <iostream>
#include <string>

using namespace std;

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
