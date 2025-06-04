#ifndef RETVAL_HPP
#define RETVAL_HPP

#include <concepts>

template <typename F, typename T>
concept retval = requires (F f, T t)
{
  {f()} -> std::same_as<T>;

  // The following does the same:
  // std::same_as<decltype(f()), T>;

  // This one is interesting too:
  // t = f();
};

#endif // RETVAL_HPP
