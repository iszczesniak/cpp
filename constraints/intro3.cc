#include <string>
#include <type_traits>

using namespace std;

template <typename T> requires std::is_integral_v<T>
void
inc(T &t)
{
  ++t;
}

template <unsigned I> requires (I != 0)
int
divide(int t)
{
  return t / I;
}

int
main()
{
  auto x = 1;
  inc(x);

  auto y = .1;
  // Error: double is not an integral.
  // inc(y);

  divide<2>(2);
  // Error: the argument cannot be 0.
  // divide<0>(2);
}
