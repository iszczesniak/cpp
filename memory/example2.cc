#include "hack.hpp"

A g()
{
  return A("Hello World!");
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
