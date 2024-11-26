#include <iostream>

auto max(auto a, auto b)
{
  if (a < b)
    return b;

  return a;
}

int main()
{
  std::cout << max(1, 2) << std::endl;

  // std::cout << max(1, .1) << std::endl;
}
