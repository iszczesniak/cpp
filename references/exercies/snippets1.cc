#pragma GCC diagnostic ignored "-Wunused-value"

#include <iostream>
#include <utility>

int &loo()
{
  static int i;
  std::cout << __PRETTY_FUNCTION__ << '\n';
  return i;
}

int roo()
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
  return 0;
}

void foo(int &)
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void foo(int &&)
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

struct A
{
  A &foo() &
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return *this;
  }
  
  A &&foo() &&
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return std::move(*this);
  }
};

int main()
{
  // The & operator expects an lvalue.
  // &1; // Error: 1 is an rvalue.
  int i;
  // OK: lvalue provided.
  int *p = &i;  
  // The & expression is an rvalue.
  int * && r1 = &i;
  // An lvalue reference can bind to an lvalue only.  There is no
  // (implicit or explicit) category conversion that would convert the
  // rvalue of &i to the expected lvalue.
  // int * & r2 = &i;

  // The * operator expects an rvalue.
  *static_cast<int *>(0);
  // Expression `p` is implicitly converted from an lvalue to an
  // rvalue.
  *p;
  // We can explicitly convert `p` to an rvalue, but it's not needed.
  *std::move(p);
  // The * expression is an lvalue.
  int &r3 = *p;
  // Error: the lvalue of *p will not be implicitly converted to an rvalue.
  // int &&r4 = *p;

  // A call expression to loo is an lvalue.
  &loo();
  // A call expression to roo is an rvalue.
  // &roo(); // Error: an lvalue expected.

  // The first overload called.
  foo(*p);
  // The second overload called.
  foo(std::move(*p));  

  A a;
  A *p2 = &a;
  (*p2).foo();
  (std::move(*p2)).foo();
}
