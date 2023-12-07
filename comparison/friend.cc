#include <compare>
#include <iostream>

struct A
{
  //  auto operator <=> (const A&) const = default;

  // It's not friendship declaration, it's friend definition.
  friend auto operator <=> (const A&, const A&) = default;
};

//auto operator <=> (const A&, const A&) = default;

int
main()
{
  A a1;
  A a2;

  std::cout << (a1 < a2) << std::endl;

  // Implicitly defaulted operator ==.
  a1 == a2;
}
