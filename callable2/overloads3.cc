#include <functional>
#include <iostream>

// Regular functions -------------------------------------------------
void foo(int &x)
{
  std::cout << "Lvalue overload\n";
}

void foo(int &&x)
{
  std::cout << "Rvalue overload\n";
}

void goo()
{
}

// A template function -----------------------------------------------
template <typename T>
void goo(T)
{
}

struct A
{
  // Member functions ------------------------------------------------
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

  // Regular function call -------------------------------------------
  foo(x);
  foo(1);

  // We don't want to use static_cast, it's not generic.
  std::invoke(static_cast<void(*)(int &)>(foo), x);
  std::invoke(static_cast<void(*)(int &&)>(foo), 1);
  // std::invoke(foo, x);
  // std::invoke(foo, 1);

  // std::apply(foo, std::forward_as_tuple(x));
  // std::apply(foo, std::forward_as_tuple(1));

  // Template function call ------------------------------------------
  goo();
  goo(1);

  // std::invoke(goo);
  // std::invoke(goo, 1);

  // std::apply(goo, std::make_tuple());
  // std::apply(goo, std::forward_as_tuple(1));

  // Member function call --------------------------------------------
  a.foo();
  A().foo();

  // std::invoke(&A::foo, a);
  // std::invoke(&A::foo, A());

  // std::apply(&A::foo, std::forward_as_tuple(a));
  // std::apply(&A::foo, std::forward_as_tuple(A()));
}
