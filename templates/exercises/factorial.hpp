#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

template<typename T, T N>
constexpr T factorial()
{
  if constexpr (N)
    return N * factorial<T, N - 1>();
  else
    return 1;
}

#endif // FACTORIAL_HPP
