#include <iostream>

int main()
{
  struct A
  {
    A()
    {
      std::cout << "ctor: " << this << std::endl;
    }
  };

  try
    {
      // "A()" is an rvalue.
      throw A();
    }
  // Catch the exception by reference.  It's a non-const reference!
  catch (A &a)
    {
      // "a" is an lvalue.
      std::cout << "catch: " << &a << std::endl;
    }
}
