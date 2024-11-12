#include <concepts>
#include <iostream>

void foo(int * i)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void foo(const int * i)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int i = 1;
  const int j = 2;
  foo(&i);
  foo(&j);
}
