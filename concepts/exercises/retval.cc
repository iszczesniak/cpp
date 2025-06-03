#include "retval.hpp"

int foo();

struct callme
{
  bool operator()();
};

int main()
{
  static_assert(retval<decltype(foo), int>);
  static_assert(retval<callme, bool>);
}
