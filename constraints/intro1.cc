#include <string>

using namespace std;

template <typename T>
void
inc(T &t)
{
  ++t;
}

template <unsigned I>
int
divide(int t)
{
  return t / I;
}

int
main()
{
  int x = 1;
  inc(x);

  std::string y("Hello World!");
  // Fails at compile time because std::string is not incrementable.
  // We shouldn't be allowed to use std::string.
  // inc(y);

  divide<2>(2);
  // Fails at run time because of the division by zero.
  // We shouldn't be allowed to use 0.
  divide<0>(2);
}
