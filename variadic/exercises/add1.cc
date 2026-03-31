#include <iostream>
#include <string>

template <typename T, typename... P>
auto add(const T &t, const P &... p)
{
  if constexpr (sizeof...(p))
    return t + add(p...);
  else
    return t;
}

int
main()
{
  std::cout << add(1, 2) << std::endl;
  std::cout << add(1, 2.3) << std::endl;
  std::cout << add(std::string("Hello "), "World", '!') << std::endl;
}
