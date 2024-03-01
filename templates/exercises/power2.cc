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
  std::cout << power<unsigned long long, 2, 64>() << std::endl;
}
