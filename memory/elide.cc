#include "A.hpp"

A f()
{
  A a("f");
  return a;
}

int main()
{
  A a = g();
}
