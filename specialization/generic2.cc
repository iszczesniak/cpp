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
  std::cout << "Function foo: ";
  std::cout << t;
  std::cout << std::endl;
}

template <>
void foo<A>(const A &)
{
  std::cout << "Function foo: ";
  std::cout << "A";
  std::cout << std::endl;
}

template <>
void foo(const B &)
{
  std::cout << "Function foo: ";
  std::cout << "B";
  std::cout << std::endl;
}

int
main()
{
  foo(1);
  foo(A());
  foo(B());
}
