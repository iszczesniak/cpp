#include <cassert>

template <typename R, typename... T>
void left(R &r, T &... p)
{
  (r += ... += p);
}

template <typename R, typename... T>
void right(T &... p)
{
  (p += ... += r);
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
