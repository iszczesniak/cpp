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
  // I don't like the C syntax of the pointer to a function.
  bool (*f1a)(const int &, const int &) = foo;
  bool (*f1b)(const int &, const int &) = &foo;
  f1a(10, 20);
  (*f1a)(10, 20);
  f1b(10, 20);
  (*f1b)(10, 20);

  // A reference to a function.
  bool (&f2a)(const int &, const int &) = foo;
  // A reference cannot be initialized with a pointer.
  // bool (&f2b)(const int &, const int &) = &foo;
  f2a(10, 20);
  // The following is wierd, but it compiles. f2a is an alias for foo.
  // So f2a is replaced with foo, and foo decays into a pointer, which
  // we dereference to get a function to call.
  (*f2a)(10, 20);
  
  // The C++ syntax for a function type.
  using foo_type = bool(const int &a, const int &b);
  // Pointers to a function.
  foo_type *f3a = foo;
  foo_type *f3b = &foo;
  // A reference to a function.
  foo_type &f3c = foo;
  f3a(10, 20);
  (*f3a)(10, 20);
  f3b(10, 20);
  (*f3b)(10, 20);
  f3c(10, 20);
  (*f3c)(10, 20);
}
