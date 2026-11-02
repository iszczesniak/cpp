#include "hack.hpp"

void f(A *p)
{
  A a("f");
  a.hello();
  // The implementation of the return instruction.
  new (p) A(a);
}

int main()
{
  A a;
  f(&a);
}
