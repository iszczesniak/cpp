#include "hack.hpp"

void f(A *p)
{
  // Create the result object.
  new (p) A("f");
  A &a = *p;
  a.hello();
}

int main()
{
  A a;
  f(&a);
}
