#include <iostream>

using namespace std;

template <typename T>
void f(T)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
void f(int, T, double)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
void f(T *)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template<>
void f(int)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

void f(double)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int
main()
{
  bool b;
  int i;
  double d;

  f(b);
  f(&i);
  f(d);
}
