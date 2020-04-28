#include <iostream>

template <typename T, unsigned I>
void
foo(const T (&)[I])
{
  std::cout << "The array has " << I << " elements.\n";
}

int
main()
{
  foo({"Hello ", "World!"});
  foo({1, 2, 3, 4, 5});
}
