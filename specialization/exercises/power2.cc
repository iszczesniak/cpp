#include <iostream>

template <typename T, T M, T N>
T power()
{
  return M * power<T, M, N - 1>();
}

// The problem defies a good solution with a template specialization:
// for every pair of type and x, we have to provide a specialization.

template <>
int power<int, 2, 0>()
{
  return 1;
}

template <>
unsigned long long power<unsigned long long, 2, 0>()
{
  return 1;
}

template <>
unsigned long long power<unsigned long long, 3, 0>()
{
  return 1;
}

int
main()
{
  std::cout << power<int, 2, 10>() << std::endl;
  std::cout << power<unsigned long long, 2, 32>() << std::endl;
  std::cout << power<unsigned long long, 3, 32>() << std::endl;
}
