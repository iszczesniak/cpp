#include <iostream>

auto
foo(int a)
{
  std::cout << "&a = " << &a << std::endl;
  return  [&](){std::cout << "&a = " << &a << std::endl;};
}

int
main()
{
  foo(1)();
}
