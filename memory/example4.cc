#include "frame.hpp"
#include "hack.hpp"

A g()
{
  frame x(__PRETTY_FUNCTION__);
  return A("g");
}

A f(A a)
{
  frame x(__PRETTY_FUNCTION__);
  return a;
}

int main()
{
  frame x(__PRETTY_FUNCTION__);
  A a = f(g());
}
