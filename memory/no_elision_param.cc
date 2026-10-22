#include "A.hpp"

A foo(A a)
{
  return a;
}

int main()
{
  A a = foo(A("main"));
}
