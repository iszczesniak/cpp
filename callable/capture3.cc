#include <iostream>

using namespace std;

int
main()
{
  int x = 1, y = 2;

  // Variable x is captured by value, y by reference.
  [x, &y]() mutable {x = 10, y = 20;}();

  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
}
