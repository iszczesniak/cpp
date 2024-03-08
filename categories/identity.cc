#include <cassert>

struct A
{
  constexpr A() = default;
};

int
main()
{
  const int i1 = 1;
  const int i2 = 1;
  // Do i1 and i2 have the same identity?
  // assert(&i1 == &i2);

  constexpr int I1 = 1;
  constexpr int I2 = 1;
  // Do I1 and I2 have the same identity?
  // assert(&I1 == &I2);

  constexpr A a1, a2;
  // Do a1 and a2 have the same identity?
  // assert(&a1 == &a2);
  
  // What's the identity anyway?
}
