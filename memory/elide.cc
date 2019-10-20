#include <iostream>
#include <string>

using namespace std;

struct A
{
  string m_name;

  A()
  {
    cout << "default-ctor" << endl;
  }

  A(const A &a): m_name(a.m_name)
  {
    cout << "copy-ctor: " << m_name << endl;
  }

  ~A()
  {
    cout << "dtor: " << m_name << endl;
  }
};

int main()
{
  // That's a function declaration, though in the legacy C++ it used
  // to mean the default initialization of object "foo".
  A foo();

  // The equivalent ways of default initialization.
  {
    A a;
    A b{};
    A c = A();
    A d = A{};
  }

  // The equivalent ways of direct (with arguments) initialization.
  {
    A a("a");
    A b{"b"};
    A c = A("c");
    A d = A{"d"};
  }
}
