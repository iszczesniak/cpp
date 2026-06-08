#include <iostream>
#include <string>

// A declaration of the primary function template.
template <typename T>
void foo(const T &t);

// A declaration of a specialization.
template <>
void foo<int>(const int &);

// A definition of a specialization.
template <>
void foo<std::string>(const std::string &)
{
  std::cout << "A template specialization for std::string.\n";
}

int main()
{
  // foo(1); // Linking fails.
  // foo(.2); // Linking fails.
  foo(std::string());
}
