#include <iostream>

struct A
{
  A &operator=(const A &)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }

  A &operator=(A &&)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
};

int
main()
{
  A x, y, z;
  // No biggie.
  x = y = z;
  // This works as expected.
  x = y = A();
  // Does not work as expected.  I would expect two moves.
  x = A() = A();
  // Again, I would expect two moves.
  A() = A() = A();

  // This shouldn't compile.  Yet it does!
  A &r = A() = A();
}
