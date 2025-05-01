#include <iostream>

void foo(int)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void foo(double)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  // Calls the overload for the double, because the floating-point
  // promotion (from float to double) is better than the
  // floating-integral conversion that would be required to call the
  // overload for the integer.
  foo(.1f);
}
