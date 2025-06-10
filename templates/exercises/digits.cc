#include <iostream>

template<int D>
const char *
digitname()
{
  if constexpr (D == 0)
    return "zero";
  else if constexpr (D == 1)
    return "one";
  else
    static_assert(false, "Please pass me a digit.");
}

int
main()
{
  std::cout << digitname<0>() << std::endl;
  std::cout << digitname<1>() << std::endl;
  // std::cout << digitname<10>() << std::endl;
}
