#include <concepts>
#include <iostream>

using namespace std;

template <unsigned I, typename T> requires integral<T>
void
foo(T x)
{
  cout << "foo: integral" << endl;
}

template <unsigned I, typename T> requires (I == 0) && integral<T>
void
foo(T x)
{
  cout << "don't divide integrals by 0" << endl;
}

int
main()
{
  int x = 1;
  foo<0>(x);
  foo<1>(x);
}
