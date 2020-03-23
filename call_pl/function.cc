#include <iostream>
#include <functional>
#include <type_traits>

bool
foo(const int &a, const int &b)
{
  std::cout << "foo: a = " << a << ", b = " << b << '\n';
  return true;
}

using foo_type = bool(const int &a, const int &b);

int
main()
{
  auto f1a = foo;
  auto f1b = &foo;
  // static_assert(std::is_same_v(decltype(f1a), decltype(f1b)));

  f1a(10, 20);
  (*f1a)(10, 20);
  f1b(10, 20);
  (*f1b)(10, 20);

  bool (*f2a)(const int &, const int &) = foo;
  bool (*f2b)(const int &, const int &) = &foo;
  f2a(10, 20);
  (*f2a)(10, 20);
  f2b(10, 20);
  (*f2b)(10, 20);

  foo_type *f3a = foo;
  foo_type *f3b = &foo;
  f3a(10, 20);
  (*f3a)(10, 20);
  f3b(10, 20);
  (*f3b)(10, 20);

  std::function<bool(const int &, const int &)> f4a = foo;
  std::function<bool(const int &, const int &)> f4b = &foo;
  f4a(10, 20);
  f4b(10, 20);
  // (*f4)(10, 20); // This doesn't fly.
}
