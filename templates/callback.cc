#include <iostream>

template <typename T>
void
foo(T a, T b)
{
  std::cout << a << b;
}

template <void (&F)(int, int) = foo>
void callme(int a, int b)
{
  F(a, b);
}

void
goo(int a, int b)
{
}

int
main()
{
  std::cout << 1 << 2;

  // For GCC 13.1.0 with -O1, the following line produces the same
  // assembly code as the above line.
  callme(1, 2);

  callme<goo>(1, 2);
}
