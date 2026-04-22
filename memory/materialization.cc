#include "A.hpp"

A f()
{
  return A("f");
}

int main()
{
  // A prvalue is materialized into a temporary.
  f().hello();
  // A prvalue is materialized into variable a.
  A a = f();
}
