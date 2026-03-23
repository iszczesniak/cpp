#include "A.hpp"

void foo(A a)
{
  a.hello();
}

void goo(const A &a)
{
  a.hello();
}

int main()
{
  foo(A("foo"));
  goo(A("goo"));
}
