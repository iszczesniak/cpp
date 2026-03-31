#include "A.hpp"

A foo()
{
  return A("!");
}

int main()
{
  A && r = A("Hello");
  A("World");
  foo();
}
