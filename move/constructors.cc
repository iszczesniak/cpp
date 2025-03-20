#include <iostream>

struct A
{
  A()
  {
    std::cout << "default ctor\n";
  }

  // The copy constructor has a single parameter of type const A &.
  A(const A &)
  {
    // Copy the data from object a to *this.
    std::cout << "copy-ctor\n";
  }

  // The move constructor has a single parameter of type A &&.
  A(A &&)
  {
    // Move the data from object a to *this.
    std::cout << "move-ctor\n";
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
  // to see the move constructor called.
  A c{A()};
  // Calls the move constructor.
  A d{std::move(a)};
}
