#include <iostream>

using namespace std;

void f(int *)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
void f(T)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
void f(T *)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template <>
void f(int *)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int
main()
{
  int *i;
  f(i);
}
