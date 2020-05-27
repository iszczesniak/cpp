#include <string>

using namespace std;

template <typename T>
void
inc(T &t)
{
  static_assert(std::is_integral_v<T>, "Gimme an integral type.");
  ++t;
}

template <unsigned I>
void
foo()
{
  static_assert(I < 10, "Must be less than 10.");
}

int
main()
{
  auto x = 1;
  inc(x);

  foo<1>();

  auto y = .1;
  // Error: double is not an integral.
  // inc(y);

  // Error: the argument must be less than 10.
  // foo<10>();
}
