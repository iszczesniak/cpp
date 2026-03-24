#include "A.hpp"
#include <iostream>

void foo(bool flag)
{
  std::cout << "foo\n";
  if (flag)
    static A a;
}

int main()
{
  std::cout << "main\n";
  foo(false);
  foo(true);
  foo(true);
}
