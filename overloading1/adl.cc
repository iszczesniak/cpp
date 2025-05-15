#include <iostream>

namespace X
{
  struct A {};

  void f(A, int)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
}

namespace Y
{
  void f(X::A, unsigned)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void g()
  {
    // void f(X::A, unsigned);

    X::A a;
    f(a, 1);
  }
}

int main()
{
  Y::g();
}
