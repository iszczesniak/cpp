#include "A.hpp"

void f(A)
{
}

int main()
{
  // Constructor elided for a parameter initialization.
  f(A("Hello!"));
}
