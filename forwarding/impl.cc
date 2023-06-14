#include <iostream>
#include <type_traits>

template <typename T>
auto &&
forward(std::remove_reference_t<T> &t)
{
  return static_cast<T &&>(t);
}

template <typename T>
auto &&
forward(std::remove_reference_t<T> &&t)
{
  static_assert(std::is_same_v<std::remove_reference_t<T>, T>,
                "cannot convert");
  return static_cast<std::remove_reference_t<T> &&>(t);
}

int
main()
{
  int i = 1;
  auto &&r1 = forward<int>(i);
  ++r1;
  std::cout << i << std::endl;
  auto &r2 = forward<int &>(i);
  ++r2;
  std::cout << i << std::endl;

  // forward<int>(1);
}
