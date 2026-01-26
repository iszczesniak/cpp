#include <iostream>

struct A
{
  bool operator == (const A &) const
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return false;
  }
};

struct B: A
{
  bool operator == (const B &) const
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return false;
  }
};

int main()
{
  A a;
  B b;
  b == a;
  // b = a;
}
