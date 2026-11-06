#include "frame.hpp"
#include "hack.hpp"

void g(A *p)
{
  frame x(__PRETTY_FUNCTION__);
  new (p) A("g");
}

A f(A a = {})
{
  frame x(__PRETTY_FUNCTION__);
  g(&a);
  return a;
}

int main()
{
  frame x(__PRETTY_FUNCTION__);
  A a = f();
}
