#include <cassert>
#include <utility>

int &foo()
{
  static int i = 1;
  return i;
}

int main()
{
  double a = 0.1;
  // Variable b is of the double type.
  decltype(a) b = 1;

  int i, j = 1;
  int &x = i;

  // Variable y has the same type as variable x: an lvalue reference.
  decltype(x) y = j;
  y = 2;
  assert(j == 2);

  // Expression foo() is of the reference type to an integer, and so
  // is variable z.
  decltype(foo()) z = foo();
  z = 2;
  assert(foo() == 2);

  int &&r = 1;
  // Variable s is of the rvalue reference type to an integer.
  decltype(r) s = std::move(r);
  s = 2;
  assert(r == 2);
}
