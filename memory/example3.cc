#include "frame.hpp"
#include "hack.hpp"

A g()
{
  frame x(__PRETTY_FUNCTION__);
  return A("g");
}

A f()
{
  frame x(__PRETTY_FUNCTION__);
  A a = g();
  return a;
}

int main()
{
  frame x(__PRETTY_FUNCTION__);
  A a = f();
}
