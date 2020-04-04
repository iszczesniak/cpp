#include <iostream>

using namespace std;

template <typename T>
void foo(T t)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
void foo(T *t)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int
main()
{
  int *p;
  foo<int>(p);

  int i;
  foo<int>(i);
}
