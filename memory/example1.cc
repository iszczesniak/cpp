#include "A.hpp"

A g()
{
  return A("Hello World!");
}

A f()
{
  return g();
}

int main()
{
  A a = f();
}
