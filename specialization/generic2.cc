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
void foo(const T &);

template <>
void foo(const int &i)
{
  std::cout << i;
}

template <>
void foo(const A &)
{
  std::cout << "A\n";
}

template <>
void foo(const B &)
{
  std::cout << "B\n";
}

int
main()
{
  // foo(1);
  foo(A());
  foo(B());
}
