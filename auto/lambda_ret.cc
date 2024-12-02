#include <iostream>

int &foo()
{
  static int i = 1;

  return i;
}

int main()
{
  auto c = []() -> decltype(auto) {return foo();};

  c() = 100;

  std::cout << c() << std::endl;
}
