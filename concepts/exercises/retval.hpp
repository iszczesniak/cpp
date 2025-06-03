#ifndef RETVAL_HPP
#define RETVAL_HPP

#include <concepts>

template <typename F, typename T>
concept retval = requires (F f)
{
  {f()} -> std::same_as<T>;
};

#endif // RETVAL_HPP
