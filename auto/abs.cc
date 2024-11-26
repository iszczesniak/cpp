#include <iostream>

auto abs(auto t)
{
  if (t < 0)
    return -t;

  return t;
}

int main()
{
  std::cout << abs(-1) << std::endl;
  std::cout << abs(-1ll) << std::endl;
  std::cout << abs(-.1) << std::endl;
}
