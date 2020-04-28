#include <array>
#include <iostream>

using namespace std;

template <typename T, std::size_t I>
void
foo(const array<T, I> &)
{
  cout << "The array has " << I << " elements.\n";
}

int
main()
{
  foo(array{"Hello ", "World!"});
  foo(array{1, 2, 3, 4, 5});
}
