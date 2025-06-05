#ifndef RETVAL_HPP
#define RETVAL_HPP

#include <concepts>
#include <type_traits>

template <typename F, typename T>
concept retval = requires (F f)
{
  {f()} -> std::same_as<T>;

  // The following does the same:
  // std::same_as<decltype(f()), T>;
};

// Or as simple as this.
template <typename F, typename T>
concept retval2 = std::is_invocable_r_v<T, F>;

template <typename F, typename T>
concept retval3 = requires (F f, T t)
{
  // The following is interesting, but tests whether an value of T is
  // assignable with the result of f(), which can involve conversion,
  // overloading of `operator=`.
  t = f();
};


#endif // RETVAL_HPP
