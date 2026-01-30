#include <string>
#include <utility>

template<typename T, typename... P>
T
factory(P &&... p)
{
  return T(std::forward<P>(p)...);
}

// template<typename T>
// T
// factory(auto &&... p)
// {
//   return T(std::forward<decltype(p)>(p)...);
// }

int
main()
{
  auto s = factory<std::string>("Hello!");
  auto c = factory<std::pair<int, int>>(1, 2);
}
