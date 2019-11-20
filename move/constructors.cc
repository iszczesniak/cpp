#include <iostream>

using namespace std;

struct A
{
  A()
  {
    cout << "default ctor\n";
  }

  // The copy constructor has a single parameter of type const A &.
  A(const A &source)
  {
    // Copy the data from object t to *this.
    cout << "copy ctor\n";
  }

  // The move constructor has a single parameter of type A &&.
  A(A &&t)
  {
    // Move the data from object t to *this.
    cout << "move ctor\n";
  }
};

int
main()
{
  A a;
  // Calls the copy constructor.
  A b{a};
  // Only the default constructor will be called, because the move
  // constructor will be elided.  Compile with -fno-elide-constructors
  A c{A()};
  // Calls the move constructor.
  A d{move(a)};
}
