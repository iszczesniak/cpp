#include <utility>

template <typename G> 
void f(G &&g) requires requires
{std::forward<G>(g)(1);}
{
  std::forward<G>(g)(1);
}

void foo()
{
}

void goo(long)
{
}

int main()
{
  // f(foo);
  f(goo);
  f([](int){});
}
