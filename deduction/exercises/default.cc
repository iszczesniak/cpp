#include <iostream>

template <typename T = int>
void foo(T t = {})
{
  std::cout << __PRETTY_FUNCTION__ << ": " << t << std::endl;
}

int main()
{
  foo(.1);
  foo<std::string>();

  // No deduction takes place as there is no argument passed.
  foo();
}
