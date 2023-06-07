#include <iostream>

using namespace std;

template <typename ...P>
void foo()
{
  cout << __PRETTY_FUNCTION__ << endl;
  cout << sizeof...(P) << endl;
}

int
main()
{
  foo<>();
  foo<int>();
  foo<bool, double>();
}
