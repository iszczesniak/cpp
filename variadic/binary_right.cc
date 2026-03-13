#include <cassert>

template <typename R, typename... T>
void left(R &r, T &... p)
{
  (r += ... += p);
}

template <typename R, typename... T>
void right(R &r, T &... p)
{
  (p += ... += r);
}

template <typename... T, typename R>
void right_right(T &... p, R &r)
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

  // This seems to be the natural order: x, y, z, but x becomes the
  // initializing expression, and so this call works wrong.
  // right(x, y, z);

  // The initializing expression has to be passed first.
  right(z, x, y);

  // If we wanted to pass the arguments in the natural order: x, y, z,
  // then the last function parameter should accept the initializing
  // expression, like the function right_right does.  Unfortunately,
  // it doesn't compile (with the newest GCC and clang on March 13,
  // 2026), because the parameter pack p gobbles up all arguments,
  // leaving none for the initialization of parameter r.
  
  assert(x == 6);
  assert(y == 5);
  assert(z == 3);
}
