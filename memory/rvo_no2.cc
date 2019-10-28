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

A foo(A a)
{
  return a;
}

int main()
{
  foo(A());
}
