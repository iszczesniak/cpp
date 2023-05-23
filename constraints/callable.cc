#include <utility>

// Check whether we could call g with 1.  I don't know how to check
// that the type of the first parameter of a callable is integral.
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
