#include <iostream>

template <typename T>
void
foo1(T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <typename T>
void
foo2(const T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <typename T>
void
foo3(volatile T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <typename T>
void
foo4(const volatile T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int
main()
{
  int x = 1;
  const int y = 2;
  const volatile int z = 3;

  foo1(x);
  foo1(y);
  foo1(z);

  foo2(x);
  foo2(y);
  foo2(z);

  foo3(x);
  foo3(y);
  foo3(z);

  foo4(x);
  foo4(y);
  foo4(z);
}
