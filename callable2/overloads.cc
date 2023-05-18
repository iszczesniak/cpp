#include <functional>
#include <iostream>

void foo(int &x)
{
  std::cout << "Lvalue overload\n";
}

void foo(int &&x)
{
  std::cout << "Rvalue overload\n";
}

struct A
{
  void foo() &
  {
  }

  void foo() &&
  {
  }
};

int
main()
{
  int x;
  A a;

  // Regular function call.
  foo(x);
  foo(1);

  // std::invoke(foo, x);
  // std::invoke(foo, 1);

  // std::apply(foo, std::forward_as_tuple(x));
  // std::apply(foo, std::forward_as_tuple(1));

  // Regular member function call.
  a.foo();
  A().foo();

  // std::invoke(&A::foo, a);
  // std::invoke(&A::foo, A());

  // std::apply(&A::foo, std::forward_as_tuple(a));
  // std::apply(&A::foo, std::forward_as_tuple(A()));
}
