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

// The version with the callback reference.
template <void (&F)(int, int) = nodebug>
void roo(int a, int b)
{
  F(a, b);
}

// The version with the callback pointer.
template <void (*F)(int, int) = nodebug>
void poo(int a, int b)
{
  F(a, b);
}

int
main()
{
  // The nodebug function is used.
  roo(1, 2);
  poo(1, 2);

  // The baseline code, the same as in the debug function.
  std::cout << 1 << 2;

  // For GCC 13.1.0 with -O1, the following line produces the same
  // assembly code as the line above.
  roo<debug>(1, 2);
  poo<debug>(1, 2);
}
