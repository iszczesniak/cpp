#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

template <typename T, T N>
T fibonacci()
{
  if constexpr (N >= 2)
    return fibonacci<T, N - 1>() + fibonacci<T, N - 2>();

  if constexpr (N == 1)
    return 1;

  return 0;
}

#endif // FIBONACCI_HPP
