#include "perfcall.hpp"

#include <cassert>
#include <concepts>
#include <iostream>

int &loo()
{
  static int i = 1;
  return i;
}

void roo()
{
  std::cout << "Hello ";
}

int main()
{
  f(loo) = 0;
  assert(loo() == 0);
  static_assert(std::same_as<decltype(f(loo)), int &>);

  f(roo);
  f([]{std::cout << "World!\n";});
}
