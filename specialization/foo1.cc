#include <iostream>
#include <string>

// The definition of the primary function template.
template <typename T>
void foo(const T &t)
{
  std::cout << __PRETTY_FUNCTION__ << ": " << t << std::endl;
}

// An explicit specialization of a function template.  The argument
// for the primary template is explicitly given.
template <>
void foo<std::string>(const std::string &)
{
  std::cout << "A template specialization for std::string.\n";
}

int main()
{
  foo(1);
  foo(.2);
  foo("Hello!");
  foo(std::string());
}
