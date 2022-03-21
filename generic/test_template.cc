#include <iostream>

template <typename T>
void
foo(T a, T b)
{
  std::cout << a << b;
}

int
main()
{
  foo(1, 2);
}
