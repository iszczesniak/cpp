#include <array>
#include <iostream>

using namespace std;

template <template <typename, long unsigned> typename C, typename T>
void
foo(T t)
{
  cout << __PRETTY_FUNCTION__ << endl;
  C<T, 1> c = {t};
}

int
main()
{
  foo<array>(1);
}
