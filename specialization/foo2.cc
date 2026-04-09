#include <iostream>
#include <string>

// A declaration of the primary function template.
template <typename T>
void foo(const T &t);

// A declaration of an explicit specialization of a function template.
// The compiler deduces the arguments of the primary template.
template <>
void foo(const std::string &);

// A definition of an explicit specialization of a function template.
// The compiler deduces the arguments of the primary template.
template <>
void foo(const std::string &)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << "std::string" << std::endl;
}

// This specialization doesn't match any the primary template.
// template <>
// void foo(int);

int
main()
{
  // foo(1);
  // foo(.2);
  // foo("Hello!");
  foo(std::string("Hello!"));
}
