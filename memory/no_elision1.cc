#include <iostream>
#include <string>

using namespace std;

struct A
{
  A()
  {
    cout << "default-ctor" << endl;
  }

  A(const A &a)
  {
    cout << "copy-ctor" << endl;
  }

  ~A()
  {
    cout << "dtor" << endl;
  }
};

A foo(bool flag)
{
  // These objects have to be created, and since we don't know which
  // is going to be returned, both of them have to be created locally.
  A a, b;

  // The returned value must be copied.
  return flag ? a : b;
}

int main()
{
  foo(true);
}
