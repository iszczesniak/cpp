#include <iostream>

template <typename T>
struct C
{
};

// A declaration of the primary function template.
template <typename T>
void foo(const T &t);

// Error: a partial specialization of a function template is not
// allowed.

// template <typename T>
// void foo<C<T>>(const C<T> &)
// {
//   std::cout << __PRETTY_FUNCTION__ << ": ";
//   std::cout << "C<T>" << std::endl;
// }

// This is another primary template.  It's not a specialization.
template <typename T>
void foo(const C<T> &)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << "C<T>" << std::endl;
}

int
main()
{
  // foo(1);
  foo(C<int>());
}
