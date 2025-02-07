#include <iostream>

template <typename T>
concept comparable = requires (T t) {t <= t;};

template <comparable T>
T mymin(T t1, T t2)
{
  return t1 <= t2 ? t1 : t2;
}

int
main()
{
  std::cout << mymin(10, 1) << std::endl;
  std::cout << mymin("Hello", "World!") << std::endl;
  mymin(std::make_pair(1, 1), std::make_pair(1, 2));
}
