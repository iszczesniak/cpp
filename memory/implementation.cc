#include "A.hpp"

void g(A *p)
{
  new (p) A("g");
}

void f(A *p)
{
  g(p);
}

int main()
{
  A a("main");
  a.~A();
  f(&a);
}
