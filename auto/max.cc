#include <iostream>

auto my_max(auto a, auto b)
{
  if (a < b)
    return b;

  return a;
}

int main()
{
  std::cout << my_max(1, 2) << std::endl;

  // std::cout << my_max(1, .1) << std::endl;
}
