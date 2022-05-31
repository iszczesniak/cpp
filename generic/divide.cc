#include <iostream>

template <unsigned I>
int
divide(int t)
{
  return t / I;
}

int
divide(int t, int I)
{
  return t / I;
}

int
main()
{
  volatile int x = 2;
  // Super-fast division by bit shifting.
  std::cout << divide<2>(x) << std::endl;
  // Regular division, depending on optimizer.
  std::cout << divide(x, 2) << std::endl;
}
