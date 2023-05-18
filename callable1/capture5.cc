#include <iostream>

int
main()
{
  int x = 1, y = 2;

  // Capture every variable by reference.
  [&]{x = 10; y = 20;}();

  std::cout << "x = " << x << ", y = " << y << std::endl;
}
