#include "A.hpp"

A foo()
{
  static A a("Hello!");
  return a;
}

int main()
{
  A a = foo();
}
