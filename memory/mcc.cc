#include <iostream>

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

A foo()
{
  return A();
}

A a = foo();

int main()
{
}
