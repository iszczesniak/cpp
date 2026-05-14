#include <functional>
#include <iostream>

// A template function -----------------------------------------------
template <typename T>
void goo(T)
{
}

int
main()
{
  // Template function call ------------------------------------------
  goo(1);

  std::invoke<void(int)>(goo, 1);
  std::invoke<void(*)(int)>(goo, 1);
  std::invoke<void(&)(int)>(goo, 1);

  void(*p)(int) = goo;
  p(1);
  void(&r)(int) = goo;
  r(1);

  std::invoke(static_cast<void(*)(int)>(goo), 1);
  std::invoke(static_cast<void(&)(int)>(goo), 1);
}
