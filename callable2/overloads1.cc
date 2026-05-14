#include <functional>
#include <iostream>

void foo(int &x)
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void foo(int &&x)
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

int
main()
{
  int x;
  foo(x);
  foo(1);

  // std::invoke(foo, x);
  // std::invoke(foo, 1);

  std::invoke<void(int &)>(foo, x);
  std::invoke<void(int &&)>(foo, 1);

  void(*pl)(int &) = foo;
  pl(x);
  void(*pr)(int &&) = foo;
  pr(1);

  std::invoke(static_cast<void(*)(int &)>(foo), x);
  std::invoke(static_cast<void(*)(int &&)>(foo), 1);
}
