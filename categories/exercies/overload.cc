#include <iostream>
#include <utility>

struct A
{
  void operator ++() &
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void operator ++() &&
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int
main()
{
  A a;
  ++a;
  ++A();
}
