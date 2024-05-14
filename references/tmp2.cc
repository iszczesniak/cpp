#include <iostream>

struct A
{
  ~A()
  {
    std::cout << "dtor of A\n";
  }
};

struct B
{
  // ACHTUNG!  These initializations are ill-formed! Does the compiler
  // complain?  Clang 11 does, but GCC 12 doesn't.
  const A &a = A();
  const int &i = 1;
};

int
main()
{
  const B &b = B();
  std::cout << "&b   = " << &b << '\n';
  std::cout << "&b.a = " << &b.a << '\n';
}
