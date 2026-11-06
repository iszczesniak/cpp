#include "frame.hpp"
#include "hack.hpp"

void g(A *p)
{
  frame x(__PRETTY_FUNCTION__);
  new (p) A("g");
}

void f(A *p)
{
  frame x(__PRETTY_FUNCTION__);
  return g(p);
}

int main()
{
  frame x(__PRETTY_FUNCTION__);
  A a;
  f(&a);
}
