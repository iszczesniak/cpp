#include <iostream>

void foo(float)
{
  std::cout << __PRETTY_FUNCTION << std::endl;
}

void foo(long double)
{
  std::cout << __PRETTY_FUNCTION << std::endl;
}

int main()
{
  foo(.1);
}
