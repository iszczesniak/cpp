#include <iostream>

void foo(int)
{
  std::cout << "";
}

void foo(double)
{
  std::cout << "";
}

int main()
{
  // Integral promotion is prefered over floating-point conversion.
  foo('c');
}
