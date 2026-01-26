#include <iostream>

struct A
{
  void operator = (const A &)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

struct B: A
{
  void operator = (const B &)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int main()
{
  A a;
  B b;
  a = b;
  b = a;
}
