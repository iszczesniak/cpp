#include <iostream>

template <typename T, T M, T N>
T power()
{
  if constexpr (N)
    return M * power<T, M, N - 1>();

  return 1;
}

int
main()
{
  std::cout << power<int, 2, 10>() << std::endl;
  // Take a look at the symbol table of the executable.  There are 33
  // template functions generated!
  std::cout << power<unsigned long long, 2, 32>() << std::endl;
}
