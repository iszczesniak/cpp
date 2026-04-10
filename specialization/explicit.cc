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

// This is another primary template.  It's not a specialization.  How
// does it differ from the specialization above?
template <typename T, std::size_t I>
void foo(const std::array<T, I> &)
{
  std::cout << "A template overload: "
            << __PRETTY_FUNCTION__ << std::endl;
}

int
main()
{
  foo(std::array{1, 2, 3});
}
