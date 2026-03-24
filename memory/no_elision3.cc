#include "A.hpp"

// Global data.
A a("global");

A foo()
{
  // This one overshadows the global "a".
  static A a("static");
  return a;
}

A goo()
{
  return a;
}

int main()
{
  foo();
  goo();
}
