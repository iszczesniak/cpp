#include <iostream>

template <typename T>
decltype(auto) foo()
{
  return 0;
}

template <>
decltype(auto) foo<int>()
{
  return "Hello!";
}

int main()
{
  foo<int>();
}
