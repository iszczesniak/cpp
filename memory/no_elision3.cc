#include "A.hpp"

// Global data.
A a("global");

A foo()
{
  // static A a("static");
  return a;
}

int main()
{
  foo();
}
