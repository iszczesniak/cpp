#include <iostream>

void foo(double)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void foo(int)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  // The argument is 0 of type float.
  foo(.0f);
}
