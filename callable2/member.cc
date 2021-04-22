#include <chrono>
#include <iostream>
#include <functional>
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

  // A pointer to a member function.
  void (A::* p1)(int) = &A::foo;
  // It's better to let the compiler deduce the type.
  auto p2 = &A::goo;

  (a.*p1)(1);
  (b.*p1)(1);
  (a.*p2)(1);
  (b.*p2)(1);
}
