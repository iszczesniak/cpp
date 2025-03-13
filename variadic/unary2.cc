#include <cassert>

template <typename... T>
void left(T &... p)
{
  (... += p);
}

template <typename... T>
void right(T &... p)
{
  (p += ...);
}

int main()
{
  int x = 1, y = 2, z = 3;

  // We would like to inrement y by z, and then x by y:
  //
  // x += y += z;
  //
  // The above compiles and works as expected, because += has the
  // right associativity, and so we need the right fold expression.

  // left(x, y, z);
  right(x, y, z);

  assert(x == 6);
  assert(y == 5);
  assert(z == 3);
}
