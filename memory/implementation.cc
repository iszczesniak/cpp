#include "A.hpp"

void g(A &a)
{
  new (&a) A("g");
}

void f(A &a)
{
  g(a);
}

int main()
{
  A a("main");
  a.~A();
  f(a);
}
