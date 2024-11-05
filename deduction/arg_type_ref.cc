#include <iostream>

template <typename T>
void
foo(T &t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

// Can't overload for reference types of different top-level
// qualifiers because no such thing exists!
// template <typename T>
// void
// foo(T & const t)
// {
//   std::cout << __PRETTY_FUNCTION__ << std::endl;
// }

template <typename T>
void
foo(T volatile &t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

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
