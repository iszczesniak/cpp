#include <string>

using namespace std;

template <typename T>
void
inc(T &t)
{
  static_assert(std::is_arithmetic_v<T>, "Gimme an arithmetic type.");
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
  int x = 1;
  inc(x);

  foo<1>();

  std::string y("Hello World!");
  // This would not compile, because std::string is not arithmetic.
  // inc(y);

  // This would not compile:the argument must be less than 10.
  // foo<10>();
}
