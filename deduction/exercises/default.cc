#include <iostream>

template <typename T = int>
void foo(T t = {})
{
  std::cout << __PRETTY_FUNCTION__ << ": " << t << std::endl;
}

int main()
{
  foo();
  foo(.1);
  foo<std::string>();
}
