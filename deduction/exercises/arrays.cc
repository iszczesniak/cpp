#include <array>
#include <iostream>

using namespace std;

template <typename T, unsigned I>
unsigned
foo(const T (&)[I])
{
  cout << __PRETTY_FUNCTION__ << endl;
  return I;
}

template <typename T, std::size_t I>
std::size_t
foo(const array<T, I> &)
{
  cout << __PRETTY_FUNCTION__ << endl;
  return I;
}

int
main()
{
  cout << foo({"Hello", "World!"}) << endl;
  cout << foo({1, 2, 3, 4, 5}) << endl;

  cout << foo(array{"Hello ", "World!"}) << endl;
  cout << foo(array{1, 2, 3, 4, 5}) << endl;
}
