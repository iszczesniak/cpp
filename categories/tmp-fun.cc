#include <iostream>

struct A
{
  A()
  {
    std::cout << "ctor: " << this << std::endl;
  }
};

// "a" is a parameter of a const reference type.
void
foo(const A &a)
{
  // "a" is an lvalue.
  std::cout << "foo: " << &a << std::endl;
}

int main()
{
  // "A()" is an rvalue.
  foo(A());
}
