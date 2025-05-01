#include <iostream>

void foo(float)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void foo(long double)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  foo(.1);
}
