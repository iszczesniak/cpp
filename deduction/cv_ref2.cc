#include <iostream>
#include <utility>

void foo(int &)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void foo(const int &)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int i = 1;

  foo(i);
  foo(std::as_const(i));
}
