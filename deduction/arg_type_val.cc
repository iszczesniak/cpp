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

  int &rx = x;
  const int &ry = y;
  const volatile int &rz = z;

  foo1(rx);
  foo1(ry);
  foo1(rz);

  foo2(rx);
  foo2(ry);
  foo2(rz);

  foo3(rx);
  foo3(ry);
  foo3(rz);

  foo4(rx);
  foo4(ry);
  foo4(rz);

  int * const volatile cvpx = &x;
  const int * const volatile cvpy = &y;
  const volatile int * const volatile cvpz = &z;

  foo1(cvpx);
  foo1(cvpy);
  foo1(cvpz);

  foo2(cvpx);
  foo2(cvpy);
  foo2(cvpz);

  foo3(cvpx);
  foo3(cvpy);
  foo3(cvpz);

  foo4(cvpx);
  foo4(cvpy);
  foo4(cvpz);
}
