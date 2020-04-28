#include <array>
#include <iostream>

using namespace std;

template <template <typename, std::size_t> typename C, std::size_t I>
void
foo(const C<int, I> &c)
{
  cout << "Got " << I << " elements\n";
}

int
main()
{
  foo(array{1, 2, 3});
}
