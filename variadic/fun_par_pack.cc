#include <iostream>

using namespace std;

template <typename... P>
void foo(P... p)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int
main()
{
  foo();
  foo(1);
  foo(1, 2.0);
}
