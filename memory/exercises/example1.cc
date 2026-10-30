#include "frame.hpp"
#include "hack.hpp"

void g(A *a)
{
  frame x(__PRETTY_FUNCTION__);
  new (a) A("g");
}

void f(A *a)
{
  frame x(__PRETTY_FUNCTION__);
  return g(a);
}

int main()
{
  frame x(__PRETTY_FUNCTION__);
  A a;
  f(&a);
}
