#include <iostream>

using namespace std;

template <typename F>
void foo(F &f)
{
  cout << __PRETTY_FUNCTION__ << endl;
  f();
}

template <typename F>
void foo(F *f)
{
  cout << __PRETTY_FUNCTION__ << endl;
  f();
}

template <typename F>
void foo(F f)
{
  cout << __PRETTY_FUNCTION__ << endl;
  f();
}

void hello()
{
}

int main()
{
  foo(hello);
}
