#include <iostream>
#include <string>

// A declaration of the primary function template.
template <typename T>
void foo(const T &t);

// Specialization #1: the argument of the primary template deduced.
template <>
void foo(const int &);

// Specialization #2: the argument of the primary template deduced.
template <>
void foo(const std::string &)
{
  std::cout << "A template specialization for std::string.\n";
}

// Specialization #3: the deduction fails.
// template <>
// void foo(bool);

int main()
{
  // foo(1); // Linking fails.
  // foo(.2); // Linking fails.
  foo(std::string());
}
