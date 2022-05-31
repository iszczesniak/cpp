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
  // This would not compile, because std::string is not incrementable.
  // inc(y);

  divide<2>(2);
  // The template argument shouldn't be 0, yet we can use it.
  divide<0>(2);
}
