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
  float f;
  foo(f);
}
