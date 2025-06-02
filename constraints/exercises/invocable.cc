#include <concepts>

struct A
{
  void operator()();
};

void foo(int);

int
main()
{
  static_assert(std::invocable<A>);
  static_assert(!std::invocable<decltype(foo)>);
  static_assert(std::invocable<decltype(foo), int>);
}
