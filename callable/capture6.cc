#include <iostream>

using namespace std;

int
main()
{
  {
    int x = 1, y = 2;

    // Variable x is captured by value, and y by reference.
    [x, &y]() mutable {x = 10, y = 20;}();
    cout << "x = " << x << ", y = " << y << endl;
  }

  {
    int x = 1, y = 2;

    // Because of the default capture-by-value policy, x is captured
    // by value, while y is captured by reference.
    [=, &y]() mutable {x = 10, y = 20;}();
    cout << "x = " << x << ", y = " << y << endl;
  }

  {
    int x = 1, y = 2;

    // Because of the default capture-by-reference policy, x is
    // captured by reference, while y is captured by reference.
    [&, z = y]() mutable {x = 10, z = 20;}();
    cout << "x = " << x << ", y = " << y << endl;
  }

  {
    int x = 1, y = 2;

    // Because of the default capture-by-value policy, x is captured
    // by value, while y is captured by reference under name z.
    [=, &z = y]() mutable {x = 10, z = 20;}();
    cout << "x = " << x << ", y = " << y << endl;
  }
}
