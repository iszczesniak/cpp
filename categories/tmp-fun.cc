#include <iostream>

struct A
{
  A()
  {
    std::cout << "ctor: " << this << std::endl;
  }
};

void
foo(const A &a)
{
  std::cout << "foo: " << &a << std::endl;
}

int main()
{
  foo(A());
}
