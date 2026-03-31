#include "A.hpp"
#include <utility>

#pragma clang diagnostic ignored "-Wunused-value"

A &&foo()
{
  static A a("Hello!");
  return std::move(a);
}

int main()
{
  A a = foo();
  A b = static_cast<A &&>(a);
  A c = std::move(b);
}
