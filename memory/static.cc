#include <iostream>

using namespace std;

struct A
{
  A()
  {
    cout << "A" << endl;
  }
};

void foo()
{
  cout << "foo" << endl;
  static A a;
}

int main()
{
  cout << "Main" << endl;
  foo();
  foo();
}
