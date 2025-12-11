#include <iostream>

int &
g()
{
  static int a = 1;
  std::cout << a << std::endl;
  return a;
}

int main()
{
  // auto f = []() {return g();};
  auto f = []() -> decltype(auto) {return g();};
  f() = 10;
  g();
}
