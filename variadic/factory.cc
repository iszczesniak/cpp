#include <iostream>
#include <string>

template <typename T, typename ...Args>
auto
factory()
{
  return T(args...);
}

int
main()
{
  std::cout << factory<std::string>("Hello!") << std::endl;
}
