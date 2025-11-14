#include <iostream>

template <typename A>
void
foo(A a[])
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void
goo(int a[])
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int
main()
{
  int a[] = {1, 2, 3};
  foo(a);
  goo(a);
  // foo(&a);
  // goo(&a);
}
