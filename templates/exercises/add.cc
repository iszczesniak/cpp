#include <iostream>
#include <string>

template <typename Param, typename... Params>
auto add(const Param &param, const Params &... params)
{
  if constexpr (sizeof...(params))
    return param + add(params...);
  else
    return param;
}

int
main()
{
  std::cout << add(1, 2) << std::endl;
  std::cout << add(1, 2.3) << std::endl;
  std::cout << add(std::string("Hello "), "World!") << std::endl;
}
