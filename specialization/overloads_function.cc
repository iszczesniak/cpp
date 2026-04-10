#include <iostream>
#include <string>

void foo(const int &i)
{
  std::cout << "Function overload: " << i << std::endl;
}

void foo(const std::string &)
{
  std::cout << "Function overload for std::string.\n";
}

int
main()
{
  foo(1);
  foo('1');
  foo(std::string());
}
