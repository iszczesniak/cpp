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
  B();
}

