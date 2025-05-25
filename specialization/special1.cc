#include <iostream>

using namespace std;

template <typename T>
void foo(T)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
void foo(T *)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
  int x = 1;
  // Only the first overload can be used.
  foo(x);
  // Both overloads can be called, but the second is more specialized.
  foo(&x);
}
