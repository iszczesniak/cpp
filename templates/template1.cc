#include <array>
#include <iostream>

using namespace std;

template <template <typename, long unsigned> typename C, typename T>
void
foo(T t)
{
  cout << __PRETTY_FUNCTION__ << endl;
  C<T, 1> c1 = {t};
  C<T, 2> c2 = {t, t};
}

int
main()
{
  foo<array>(1);

  // This is cool: pointer to an instantiated function template.  We
  // instantiate the function right here, because we point to it.
  void (*fp)(double) = foo<array, double>;
  fp(.1);
}
