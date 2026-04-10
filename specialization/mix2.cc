#include <iostream>
#include <string>

// A definition of a primary function template.
template <typename T>
void foo(const T &t)
{
  std::cout << __PRETTY_FUNCTION__ << ": " << t << std::endl;
}

// A function overload.
void foo(const std::string &)
{
  std::cout << "Function overload for std::string.\n";
}

// A definition of an explicit specialization of a function template.
template <>
void foo(const std::string &)
{
  std::cout << "Template specialization for std::string.\n";
}

int main()
{
  foo(1);
  foo('1');
  foo(std::string());
}
