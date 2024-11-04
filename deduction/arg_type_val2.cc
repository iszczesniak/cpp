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
  int * p = &i;
  int * const cp = &i;
  int * volatile vp = &i;
  int * const volatile cvp = &i;

  foo(p);
  foo(cp);
  foo(vp);
  foo(cvp);
}
