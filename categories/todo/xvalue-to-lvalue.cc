#include "A.hpp"
#include <iostream>
#include <utility>

#pragma clang diagnostic ignored "-Wunused-value"

void foo(A &a)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  a.hello();
}

void foo(A &&a)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  a.hello();
}

int main()
{
  A a("Hello");
  // Coversion from xvalue to lvalue doesn't exist.
  // static_cast<A &>(std::move(a));

  // A const reference can be initialized with an xvalue.
  static_cast<const A &>(std::move(a));
  const A &cr = A("temp");
  A &r = const_cast<A &>(cr);
  foo(r);
}
