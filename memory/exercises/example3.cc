#include "hack.hpp"

#include <utility>

void g(A *p)
{
  new (p) A("g");
}

void f(A *p)
{
  A a;
  g(&a);
  new (p) A(a);
}

int main()
{
  A a;
  f(&a);
}
