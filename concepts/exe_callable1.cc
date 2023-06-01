#include <concepts>
#include <utility>

template <std::integral I, std::invocable<I> G>
void f(G &&g)
{
  std::forward<G>(g)(1);
}

void g(int)
{
}

int
main()
{
  f(g);
}
