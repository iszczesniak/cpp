#include <functional>
#include <iostream>

// Regular functions -------------------------------------------------
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

  // Regular function call -------------------------------------------
  foo(x);
  foo(1);

  // We don't want to use static_cast, it's not generic.
  std::invoke(static_cast<void(*)(int &)>(foo), x);
  std::invoke(static_cast<void(*)(int &&)>(foo), 1);
  // std::invoke(foo, x);
  // std::invoke(foo, 1);

  // std::apply(foo, std::forward_as_tuple(x));
  // std::apply(foo, std::forward_as_tuple(1));
}
