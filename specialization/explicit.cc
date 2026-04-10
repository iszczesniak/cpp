#include <array>
#include <iostream>

// A declaration of the primary function template.
template <typename T>
void foo(const T &t);

// Error: a partial specialization of a function template not allowed.
// template <typename T, std::size_t I>
// void foo<std::array<T, I>>(const std::array<T, I> &)
// {
//   std::cout << "A template specialization: "
//             << __PRETTY_FUNCTION__ << std::endl;
// }

// This is another primary template, not a specialization.  A
// specialization would have an explicit argument for the primary
// template.  We could argue that we removed it, so that a compiler
// can deduce it, but then this template becomes primary.
template <typename T, std::size_t I>
void foo(const std::array<T, I> &)
{
  std::cout << "A template overload: "
            << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  foo(std::array{1, 2, 3});
}
