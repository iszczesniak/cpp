#include <string>
#include <type_traits>

using namespace std;

template <typename T>
void
inc(T &t)
{
  static_assert(std::is_integral_v<T>, "Gimme an integral type.");
  ++t;
}

template <unsigned I>
int
divide(int t)
{
  static_assert(I != 0, "Cannot be 0.");
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
  // Error: the argument can not be 0.
  // divide<0>(2);
}
