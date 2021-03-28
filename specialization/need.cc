#include "library.hpp"

#include <iostream>

// A regular function overload won't cut it.
void
foo(const int &)
{
  std::cout << "overload\n";
}

// We need a specialization of the primary template.
template <>
void
foo(const int &)
{
  std::cout << "specialization\n";
}

int
main()
{
  goo(1);
}
