#include "A.hpp"

void foo(A)
{
}

int main()
{
  // Constructor elided for a parameter initialization.
  f(A("Hello!"));
}
