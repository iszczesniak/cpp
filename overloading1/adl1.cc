#include <iostream>

namespace X
{
  struct A {};

  void f(A)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
}

namespace Y
{
  void f(X::A)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void g()
  {
    // void X::f(X::A);
    void f(X::A);

    X::A a;
    f(a);
  }
}

int main()
{
  Y::g();
}
