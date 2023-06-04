#include <iostream>

using namespace std;

template <typename ...Args>
void foo(Args ...args)
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
