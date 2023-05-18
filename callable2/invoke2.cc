#include <functional>
#include <iostream>
#include <string>

using namespace std;

struct A
{
  string m_name;

  A(const string &name): m_name(name)
  {
  }

  void foo(int x)
  {
    cout << __PRETTY_FUNCTION__ << " for " << m_name << endl;
  }

  void goo(int x)
  {
    cout << __PRETTY_FUNCTION__ << " for " << m_name << endl;
  }
};

int
main()
{
  A a("a"), b("b");  
  invoke(&A::foo, a, 1);
  invoke(&A::foo, b, 2);
  invoke(&A::goo, a, 3);
  invoke(&A::goo, b, 4);
}
