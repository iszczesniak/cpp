#include "hack.hpp"

void g(A *p)
{
  new (p) A("g");
}

A f(A a)
{
  g(&a);
  return a;
}

int main()
{
  A a = f(A());
}
