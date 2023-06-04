#include <iostream>
#include <string>

struct A
{
};

template <typename ...Args>
struct B: Args...
{
  B()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int
main()
{
  // Expands to a structure type that does not have a base class.
  B<>();
  // Expands to a structure type derived from A and string.
  B<A>();
  // Expands to a structure type that has the base class A.
  B<A, std::string>();
}
