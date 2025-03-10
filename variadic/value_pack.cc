#include <iostream>

using namespace std;

template <unsigned... N>
void foo()
{
  cout << __PRETTY_FUNCTION__ << endl;
  cout << sizeof...(N) << endl;
}

int
main()
{
  foo<>();
  foo<1>();
  foo<1, 2>();
  // foo<1, -1>();
}
