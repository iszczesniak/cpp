#include <type_traits>

struct A
{
  void operator()();
};

void foo(int);

int
main()
{
  static_assert(std::is_invocable<A>::value);
  static_assert(std::is_invocable_v<A>);

  static_assert(!std::is_invocable<decltype(foo)>::value);
  static_assert(!std::is_invocable_v<decltype(foo)>);

  static_assert(std::is_invocable<decltype(foo), int>::value);
  static_assert(std::is_invocable_v<decltype(foo), int>);
}
