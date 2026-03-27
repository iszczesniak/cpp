#include "A.hpp"

#pragma clang diagnostic ignored "-Wunused-value"

A foo()
{
  static A a("Hello!");
  return a;
}

int main()
{
  A a = foo();
  static_cast<A>(a);
}
