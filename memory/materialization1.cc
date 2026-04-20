#include "A.hpp"

A g()
{
  return A("g");
}

A f()
{
  return g();
}

int main()
{
  // A prvalue is materialized into variable a.
  A a = f();
  // A prvalue is materialized into a temporary that is discarded.
  f();
}
