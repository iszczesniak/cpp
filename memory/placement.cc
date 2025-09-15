#include <iostream>

struct A
{
  const char *m_name;

  A(const char *name): m_name(name)
  {
    std::cout << "ctor: " << m_name << '\n';
  }

  ~A()
  {
    std::cout << "dtor: " << m_name << '\n';
  }
};

A g("global1");

A &singleton()
{
  static A a("singleton1");
  return a;
}

int main()
{
  A a("local1");
  a.~A();
  new(&a) A("local2");

  g.~A();
  new(&g) A("global2");

  auto &s = singleton();
  s.~A();
  new(&s) A("singleton2");
}
