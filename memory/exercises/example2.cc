#include "hack.hpp"

#include <utility>

void g(A *p)
{
  new (p) A("g");
}

void f(A *p)
{
  A a("f");
  a.~A();
  g(&a);
  new (p) A(std::move(a));
}

int main()
{
  A a("main");
  a.~A();
  f(&a);
}
