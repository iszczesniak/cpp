#include <iostream>

struct A
{
};

// B doesn't have to derive from a base class.
struct B
{
};

// A primary template
template <typename T>
void foo(const T &t)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << t << std::endl;
}

template <>
void foo<A>(const A &)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << "A" << std::endl;
}

template <>
void foo(const B &)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << "B" << std::endl;
}

int
main()
{
  foo(1);
  foo(A());
  foo(B());
}
