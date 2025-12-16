#include <iostream>

struct A
{
};

void foo(const int &i)
{
  std::cout << "Function overload: ";
  std::cout << i << std::endl;
}

void foo(const A &)
{
  std::cout << "Function overload: ";
  std::cout << "A" << std::endl;
}

int
main()
{
  foo(1);
  foo('1');
  foo(A());
}
