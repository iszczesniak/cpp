#include <iostream>
#include <string>

using namespace std;

struct A
{
  string m_name;

  A(const string &name): m_name(name)
  {
    cout << "ctor: " << m_name << endl;
  }

  A(const A &a)
  {
    cout << "copy-ctor: " << a.m_name << endl;
    m_name = a.m_name + " copy";
  }

  void hello() const
  {
    cout << "Hello from " << m_name << endl;
  }
};

A foo()
{
  A a("foo");
  return a;
}

A & goo()
{
  static A a("goo");
  return a;
}

int main()
{
  foo().hello();
  goo().hello();

  A a = foo();
  a.hello();
}
