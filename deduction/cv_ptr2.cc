#include <concepts>
#include <iostream>

void foo(int * const i)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void foo(const int * i)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int i = 1;
  int * const p1 = &i;
  const int * p2 = &i;
  foo(p1);
  foo(p2);
}
