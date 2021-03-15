#include "library.hpp"

// A regular function overload won't cut it.
void
foo(const int &)
{
}

// We need specialization of the primary template.
template <>
void
foo(const int &)
{
}

int
main()
{
  goo(1);
}
