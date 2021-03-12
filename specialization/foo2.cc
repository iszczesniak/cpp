#include <iostream>

struct A
{
};

// A declaration of the primary function template.
template <typename T>
void foo(const T &t);

// A declaration of a function template specialization.  The compiler
// deduces the arguments of the primary template.
template <>
void foo(const A &);

// A complete specialization of a function template.  The compiler
// deduces the arguments of the primary template.
template <>
void foo(const A &)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << "A" << std::endl;
}

int
main()
{
  //  foo(1);
  foo(A());
}
