#include <iostream>

using namespace std;

struct A
{
  A()
  {
    cout << "ctor" << endl;
  }

  ~A()
  {
    cout << "dtor" << endl;
  }
};

void foo(bool flag)
{
  cout << "foo" << endl;
  if (flag)
    static A a;
}

int main()
{
  cout << "Main" << endl;
  foo(false);
  foo(true);
  foo(true);
}
