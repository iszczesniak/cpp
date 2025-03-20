#include <iostream>

struct A
{
  A &operator=(A &)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }

  A &operator=(A &&) &
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }

  A &&operator=(A &&) &&
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return std::move(*this);
  }
};

int
main()
{
  A x, y;
  // This works as expected.
  x = y = A();
  // Now this works as expected.
  x = A() = A();
  // This shouldn't compile.  And now it doesn't.
  // A &r = A() = A();
}
