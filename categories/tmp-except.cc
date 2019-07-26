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
      throw A();
    }
  catch (A &a)
    {
      std::cout << "catch: " << &a << std::endl;
    }
}
