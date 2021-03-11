#include <iostream>

struct A
{
};

// B doesn't have to derive from a base class.
struct B
{
};

void foo(const int &i)
{
  std::cout << "Function foo: ";
  std::cout << i << std::endl;
}

void foo(const A &)
{
  std::cout << "Function foo: ";
  std::cout << "A" << std::endl;
}

void foo(const B &)
{
  std::cout << "Function foo: ";
  std::cout << "B" << std::endl;
}

int
main()
{
  foo(1);
  foo(A());
  foo(B());
}
