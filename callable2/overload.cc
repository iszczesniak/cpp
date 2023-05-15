#include <functional>
#include <iostream>

void foo(int &x)
{
  std::cout << "Lvalue overload\n";
}

void foo(int &&x)
{
  std::cout << "Rvalue overload\n";
}

int
main()
{
  int x;

  // Regular function call.
  foo(x);
  foo(1);

  // std::apply(foo, x);
  // std::apply(foo, 1);

  // std::invoke(foo, x);
  // std::invoke(foo, 1);
}
