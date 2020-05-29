#include <string>
#include <type_traits>

using namespace std;

template <typename T> requires std::is_integral_v<T>
void
inc(T &t)
{
  ++t;
}

template <unsigned I> requires (I < 10)
void
foo()
{
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
