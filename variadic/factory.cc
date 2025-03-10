#include <iostream>
#include <string>
#include <vector>

template <typename T, typename... P>
auto
factory(P... p)
{
  return T{p...};
}

int
main()
{
  std::cout << factory<std::string>("Hello!") << std::endl;
  auto p = factory<std::vector<int>>(1, 2, 3);
}
