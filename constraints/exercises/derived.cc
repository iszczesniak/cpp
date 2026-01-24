#include <concepts>

struct A
{
};

struct B: A
{
};

// template <typename T> requires std::derived_from<T, A>
// void foo(const T &);

// template <std::derived_from<A> T>
// void foo(const T &);

void foo(const std::derived_from<A> auto &);

int
main()
{
  A a;
  B b;

  foo(a);
  foo(b);

  foo(A{});
  foo(B{});
}
