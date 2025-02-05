#include <iostream>

using namespace std;

struct A
{
  string m_name;

  void fun(int) const
  {
    cout << __PRETTY_FUNCTION__ << ": " << m_name << endl;
  }
};

struct fun
{
  void (A::*m_f)(int) const;
  const A &m_o;

  template <typename T>
  void operator()(T &&t)
  {
    (m_o.*m_f)(forward<T>(t));
  }
};

int
main()
{
  A a1("a1"), a2("a2");

  fun(&A::fun, a1)(1);
  fun(&A::fun, a2)(1);
}
