#include <tuple>

int &g1()
{
  static int i = 1;
  return i;
}

int g2()
{
  return 1;
}

template <typename G>
decltype(auto) f(G &&g)
{
  return std::forward<G>(g)();
}

int main()
{
  auto &&r1 = f(g1);
  auto &&r2 = f(g2);
}
