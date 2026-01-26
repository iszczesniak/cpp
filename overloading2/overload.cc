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
  int *p = nullptr;
  foo<int>(p);

  int i = 0;
  foo<int>(i);
}
