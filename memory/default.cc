#include <iostream>

using namespace std;

struct A
{
  A()
  {
    cout << "default-ctor" << endl;
  }

  A()
  {
    cout << "copy-ctor" << endl;
  }
};
  
int main()
{
  A a;
  A a = A();
  A a = A{};
  A a(); // That's a function declaration!
}
