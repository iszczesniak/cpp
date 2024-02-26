#include <iostream>

template <typename T>
void
debug(T a, T b)
{
  std::cout << a << b;
}

void
nodebug(int a, int b)
{
}

template <void (&F)(int, int) = nodebug>
void foo(int a, int b)
{
  F(a, b);
}

int
main()
{
  // The nodebug function is used.
  foo(1, 2);

  // The baseline code, the same as in the debug function.
  std::cout << 1 << 2;

  // For GCC 13.1.0 with -O1, the following line produces the same
  // assembly code as the line above.
  foo<debug>(1, 2);
}
