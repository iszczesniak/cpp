#include <iostream>

int
main()
{
  int x = 1, y = 2;

  // Variable x is captured by value, y by reference.
  [x, &y]() mutable {x = 10, y = 20;}();

  std::cout << "x = " << x << ", y = " << y << std::endl;
}
