#include <iostream>

struct A
{
  A() = default;

  A(A &&a)
  {
  }
};

A foo()
{
  A a;
  return std::move(a);
}

int main()
{
  A a = foo();
}
