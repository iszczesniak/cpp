#include "A.hpp"


A foo(bool flag)
{
  // These objects have to be created, and since we don't know which
  // is going to be returned, both of them have to be created locally.
  A a("a"), b("b");

  // The returned value must be copied.
  return flag ? a : b;
}

int main()
{
  foo(true);
}
