#include <iostream>

template <typename T>
void
foo(T *t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

// Can't overload for pointer types of different top-level qualifiers.
// template <typename T>
// void
// foo(T * const t)
// {
//   std::cout << __PRETTY_FUNCTION__ << std::endl;
// }

template <typename T>
void
foo(T volatile *t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int
main()
{
  int i = 1;
  int const volatile * p1 = &i;
  int volatile * const p2 = &i;
  int const * volatile p3 = &i;
  int * const volatile p4 = &i;

  foo(p1);
  foo(p2);
  foo(p3);
  foo(p4);
}
