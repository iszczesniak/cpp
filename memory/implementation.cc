#include "A.hpp"

void f(A *p)
{
  new (p) A("g");
}

int main()
{
  A a("main");
  a.~A();
  f(&a);
}
