#include <cassert>
#include <iostream>

// Parameter N is of the value kind and type T.
template <typename T, T N>
T fibonacci()
{
  if constexpr (N >= 2)
    return fibonacci<T, N - 1>() + fibonacci<T, N - 2>();

  if constexpr (N == 1)
    return 1;

  return 0;
}

int
main()
{
  assert((fibonacci<int, 0>() == 0));
  assert((fibonacci<int, 1>() == 1));
  assert((fibonacci<int, 2>() == 1));
  assert((fibonacci<int, 19>() == 4181));

  std::cout << fibonacci<unsigned long long, 19>() << std::endl;
}
