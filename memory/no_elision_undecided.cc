#include "A.hpp"

A foo(bool flag)
{
  // This object is created here.  We refer to it by name later.
  A a("true");

  // Named elision cannot be uses when returning the value of a.
  return flag ? a : A("false");
}

int main()
{
  foo(true);
  foo(false);
}
