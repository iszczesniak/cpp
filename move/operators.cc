#include <iostream>

using namespace std;

struct A
{
  A()
  {
    cout << "default ctor\n";
  }

  // The copy assignment operator:
  // * has a single parameter of type const A &,
  // * returns A &.
  A &
  operator=(const A &source)
  {
    cout << "copy assign\n";
    return *this;
  }

  // The move assignment operator:
  // * has a single parameter of type A &&,
  // * returns A &.
  A &
  operator=(A &&t)
  {
    // Move the data from object t to *this.
    cout << "move assign\n";
    return *this;
  }
};

int
main()
{
  A a, b;
  // Calls the copy assignment operator.
  a = b;
  // Calls the move assignment operator.
  a = A();
}
