#include "hack.hpp"

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
