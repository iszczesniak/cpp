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
};

int main()
{
  A a = A();
}
