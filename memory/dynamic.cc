#include <iostream>
#include <string>

using namespace std;

struct A
{
  A()
  {
    cout << "ctor\n";
  }

  ~A()
  {
    cout << "dtor\n";
  }
};

A * factory()
{
  return new A();
}

int main()
{
  A *p = factory();
  delete p;

  cout << "Bye!" << endl;
}
