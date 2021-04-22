#include <functional>
#include <iostream>
#include <string>

using namespace std;

struct A
{
  string m_name;

  A(string name): m_name(std::move(name))
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
  invoke(&A::foo, a, 2);
  invoke(&A::foo, a, 3);
  invoke(&A::foo, a, 4);
}
