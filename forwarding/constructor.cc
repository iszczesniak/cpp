#include <iostream>

struct A
{
  // Here t is a forwarding reference.
  template <typename T>
  A(T &&t)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

template <typename T>
struct B
{
  // Here t is not a forwarding reference, just an rvalue reference.
  B(T &&t)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int
main()
{
  int x;

  // Work the way we could expect from a forwarding reference.
  A a1(1);
  A a2(x);

  B b1(1);
  // An rvalue reference cannot bind to an lvalue.
  // B b2(x);
}
