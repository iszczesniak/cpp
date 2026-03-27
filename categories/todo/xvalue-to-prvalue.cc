#include "A.hpp"
#include <utility>

A foo()
{
  static A a("Hello!");
  return std::move(a);
}

int main()
{
  A a = foo();
  static_cast<A>(std::move(a));
}
