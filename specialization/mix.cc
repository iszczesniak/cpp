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

// A definition of a complete specialization of a function template.
template <>
void foo(const A &)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << "A" << std::endl;
}

// void foo(const A &)
// {
//   std::cout << __PRETTY_FUNCTION__ << ": ";
//   std::cout << "A" << std::endl;
// }

int
main()
{
  foo(1);
  foo(.2);
  foo(A());
}
