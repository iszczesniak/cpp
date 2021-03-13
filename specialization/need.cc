#include <iostream>

// The definition of the primary function template.
template <typename T>
void foo(const T &t);

template <typename T>
void goo(const T &t)
{
  foo(t);
}

template <>
void
foo(const int &)
{
}

int
main()
{
  goo(1);
}
