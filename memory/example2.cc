#include "hack.hpp"

A g()
{
  return A("g");
}

A f()
{
  A a = g();
  return a;
}

int main()
{
  A a = f();
}
