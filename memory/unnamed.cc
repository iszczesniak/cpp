#include "A.hpp"

A f()
{
  return A("f");
}

int main()
{
  A a = f();
}
