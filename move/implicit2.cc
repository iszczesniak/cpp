#include <iostream>

struct A
{
  A() = default;

  A(A &&)
  {
    std::cout << "move ctor\n";
  }
};

struct B: A {};

A foo()
{
  B b;
  return b;
}

int
main()
{
  foo();
}
