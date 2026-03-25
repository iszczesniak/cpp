#include "A.hpp"

int main()
{
  // The equivalent ways of direct (with arguments) initialization.
  A a("a");
  A b{"b"};
  A c = A("c");
  A d = A{"d"};
  A e(A{"e"});
  A f{A("f")};

  // Acceptable and interesting, but we don't code like that.
  A g = A(A("e"));
  A h = A{A{"f"}};

  // That's a function declaration, though in the legacy C++ it used
  // to mean the default initialization of object x.
  A x(); 

  // The equivalent ways of default initialization.  To make it
  // compile, add a default constructor to type A.

  // A a;
  // A b{};
  // A c = A();
  // A d = A{};
  // A e(A{});
  // A f{A()};

  // // Acceptable and interesting, but we don't code like that.
  // A g = A(A());
  // A h = A{A{}};
}
