#include <iostream>

using namespace std;

struct A
{
  A()
  {
    cout << "default-ctor" << endl;
  }

  A(const A &)
  {
    cout << "copy-ctor" << endl;
  }

  ~A()
  {
    cout << "default-dtor" << endl;
  }
};

int main()
{
  // The equivalent ways of default initialization.
  A a;
  A b{};
  A c = A();
  A d = A{};

  // That's a function declaration, though in the legacy C++ it used
  // to mean the default initialization of object "foo".
  A foo();
}
