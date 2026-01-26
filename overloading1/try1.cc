#include <iostream>

void foo(int)
{
  std::cout << "";
}

// void foo(int &)
// {
//   std::cout << "";
// }

int main()
{
  int x;
  foo(x);
}
