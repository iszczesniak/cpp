#include "A.hpp"

int main()
{
  // That's a function declaration, though in the legacy C++ it used
  // to mean the default initialization of object "foo".
  // A foo();

  // The equivalent ways of default initialization.
  {
    A a;
    A b{};
    A c = A();
    A d = A{};
    A e(A{});
    A f{A()};

    // Acceptable and interesting, but we don't code like that.
    A g = A(A());
    A h = A{A{}};
  }

  // The equivalent ways of direct (with arguments) initialization.
  {
    A a("a");
    A b{"b"};
    A c = A("c");
    A d = A{"d"};
    A e(A{"e"});
    A f{A("f")};

    // Acceptable and interesting, but we don't code like that.
    A g = A(A("e"));
    A h = A{A{"f"}};
  }

  // Copy elided for a parameter
  f(A());
  f(A("Hello!"));

  // Copy elided for a result.
  A a = g();
}
