#include <iostream>

using namespace std;

int
main()
{
  int x = 1, y = 2;

  // Capture every variable by value.
  [&]() mutable {x = 10; y = 20;}();

  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
}
