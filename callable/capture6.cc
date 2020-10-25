#include <iostream>

using namespace std;

int
main()
{
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
    // captured by reference, while y is captured by value.
    [&, y]() mutable {x = 10, y = 20;}();
    cout << "x = " << x << ", y = " << y << endl;
  }

  {
    int x = 1, y = 2;

    // We name the captured variables differently: a, b.
    [a = x, &b = y]() mutable {a = 10, b = 20;}();
    cout << "x = " << x << ", y = " << y << endl;
  }
}
