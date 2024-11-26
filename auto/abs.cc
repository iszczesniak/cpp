#include <iostream>

auto my_abs(auto t)
{
  if (t < 0)
    return -t;

  return t;
}

int main()
{
  std::cout << my_abs(-1) << std::endl;
  std::cout << my_abs(-1ll) << std::endl;
  std::cout << my_abs(-.1) << std::endl;
}
