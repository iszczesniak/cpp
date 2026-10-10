#include "hack.hpp"

void f(A *p)
{
  new (p) A("g");
}

int main()
{
  A a;
  f(&a);
}
