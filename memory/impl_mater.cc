#include "hack.hpp"

void f(A *p)
{
  new (p) A("f");
}

int main()
{
  A a;
  f(&a);
}
