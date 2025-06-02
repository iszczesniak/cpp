#include <concepts>
#include <utility>

template <std::integral I>
void f(std::invocable<I> auto &g)
{
  g(1);
}

void i1(int)
{
}

void i2(long)
{
}

void d1(double)
{
}

int
main()
{
  // I don't know how to make the template deduce the first argument
  // of the allable, so that we could make sure it is integral.  We
  // have to provide it explicitly.
  f<int>(i1);
  f<long>(i2);
  // f<double>(d1);
}
