#include <iostream>

struct A
{
  A &operator=(A &)
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
  A x, y;
  x = y = A();
  A &r = A() = A();
}
