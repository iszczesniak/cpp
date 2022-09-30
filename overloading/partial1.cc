#include <iostream>

using namespace std;

template <typename T>
void foo(T &)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T>
void foo(const T &)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
  int x = 1;
  foo(x);

  const int cx = 1;
  foo(cx);  
}
