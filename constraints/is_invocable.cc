#include <type_traits>

struct A
{
  void operator()();
};

int
main()
{
  static_assert(std::is_invocable<A>::value);
}
