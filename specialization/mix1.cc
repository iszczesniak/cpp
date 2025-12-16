#include <iostream>

struct A
{
};

// The definition of the primary function template.
template <typename T>
void foo(const T &t)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << t << std::endl;
}

// A function overload.
void foo(const A &)
{
  std::cout << "Function overload: ";
  std::cout << "A" << std::endl;
}

int
main()
{
  foo(1);
  foo('1');
  foo(A());
}
