#include <iostream>

bool
foo(const int &a, const int &b)
{
  std::cout << "foo: a = " << a << ", b = " << b << '\n';
  return true;
}

int
main()
{
  // I don't like the pointer-to-function C syntax.
  bool (*f2a)(const int &, const int &) = foo;
  bool (*f2b)(const int &, const int &) = &foo;
  f2a(10, 20);
  (*f2a)(10, 20);
  f2b(10, 20);
  (*f2b)(10, 20);

  // That's better.
  using foo_type = bool(const int &a, const int &b);
  foo_type *f3a = foo;
  foo_type *f3b = &foo;
  f3a(10, 20);
  (*f3a)(10, 20);
  f3b(10, 20);
  (*f3b)(10, 20);
}
