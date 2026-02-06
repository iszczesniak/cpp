#include <iostream>

using namespace std;

struct A
{
  A()
  {
    cout << "ctor\n";
  }

  A(const A &)
  {
    cout << "copy ctor\n";
  }
  
  ~A()
  {
    cout << "dtor\n";
  }
};

A g()
{
  cout << "Before creating A.\n";
  return {};
}

A &&f()
{
  cout << "Before calling g.\n";
  return g();
}

int main()
{
  cout << "Before calling f.\n";
  A a = f();
}
