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

  A(const A &a): m_name(a.m_name + " copied")
  {
    cout << "copy-ctor: " << m_name << endl;
  }

  A(A &&a): m_name(a.m_name + " moved")
  {
    cout << "move-ctor: " << m_name << endl;
  }

  ~A()
  {
    cout << "dtor: " << m_name << endl;
  }
};

A g()
{
  return A("Hello World!");
}

A f()
{
  A a = g();
  return a;
}

int main()
{
  A a = f();
}
