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
    // Needed to bypass the overload resolution.
    void f(X::A);

    // Find out why exactly the following is not allowed.
    // void X::f(X::A);

    X::A a;
    f(a);
  }
}

int main()
{
  Y::g();
}
