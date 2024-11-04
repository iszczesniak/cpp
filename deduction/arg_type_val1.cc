#include <iostream>

template <typename T>
void
foo(T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

// We cannot overload templates with parameters of regular types that
// differ with qualifiers.

// template <typename T>
// void
// foo(const T t)
// {
// }

int
main()
{
  int w = 1;
  const int x = 2;
  volatile int y = 3;
  const volatile int z = 4;

  foo(w);
  foo(x);
  foo(y);
  foo(z);
}
