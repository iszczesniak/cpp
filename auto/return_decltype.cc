#include <iostream>

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
decltype(auto) f(G g)
{
  return g();
}

int main()
{
  f(g1) = 2;
  std::cout << g1() << std::endl;

  // Does not compile, because we can't assign to an rvalue.
  // f(g2) = 2;
}
