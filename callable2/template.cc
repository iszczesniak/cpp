#include <functional>
#include <iostream>

template <typename T>
void goo(T)
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

template <typename T>
void call(T)
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

int
main()
{
  goo(1);

  // std::invoke(goo, 1);

  // call(goo);
  call<void(int)>(goo);
  // In this example, we could do without the goo function.
  call<void(int)>(call);

  void(*p)(int) = goo;
  p(1);
  void(&r)(int) = goo;
  r(1);

  std::invoke<void(int)>(goo, 1);
  std::invoke<void(*)(int)>(goo, 1);
  std::invoke<void(&)(int)>(goo, 1);

  // std::invoke(static_cast<void(int)>(goo), 1);
  std::invoke(static_cast<void(*)(int)>(goo), 1);
  std::invoke(static_cast<void(&)(int)>(goo), 1);
}
