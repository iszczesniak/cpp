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
  const A &a = A();
};

int
main()
{
  const B &b = B();
  std::cout << "&b   = " << &b << '\n';
  std::cout << "&b.a = " << &b.a << '\n';
}
