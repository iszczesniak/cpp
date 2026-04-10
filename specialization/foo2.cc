#include <iostream>
#include <string>

// A declaration of the primary function template.
template <typename T>
void foo(const T &t);

// A declaration of an explicit specialization of a function template.
// The compiler deduces the arguments of the primary template.
template <>
void foo(const int &);

// A definition of an explicit specialization of a function template.
// The compiler deduces the arguments of the primary template.
template <>
void foo(const std::string &)
{
  std::cout << "A template specialization for std::string.\n";
}

int main()
{
  // foo(1); // Fails at linking.
  // foo(.2); // Fails at linking.
  foo(std::string());
}
