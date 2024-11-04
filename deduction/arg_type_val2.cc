#include <iostream>

template <typename T>
void
foo(const T t)
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
