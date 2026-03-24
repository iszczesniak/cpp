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
  A a = f();
}
