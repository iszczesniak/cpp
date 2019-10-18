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

void foo(A a)
{
  a.hello();
}

void goo(const A &a)
{
  a.hello();
}

int main()
{
  foo(A("test1"));
  goo(A("test2"));
}
