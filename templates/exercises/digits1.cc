#include <iostream>

template<int D>
const char *
digitname();

template <>
const char *
digitname<0>()
{
  return "zero";
}

template <>
const char *
digitname<1>()
{
  return "one";
}

int
main()
{
  std::cout << digitname<0>() << std::endl;
  std::cout << digitname<1>() << std::endl;
  // std::cout << digitname<10>() << std::endl;
}
