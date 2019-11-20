#include <iostream>

using namespace std;

struct A
{
  string m_name;

  A(const string &name): m_name(name)
  {
    cout << "default-ctor: " << m_name << '\n';
  }

  // The copy constructor:
  // * has a single parameter of type const A &,
  // * returns nothing (because it's a constructor).
  A(const A &source): m_name(source.m_name)
  {
    cout << "copy-ctor: " << m_name << '\n';
  }

  // The move constructor:
  // * has a single parameter of type A &&,
  // * returns nothing (because it's a constructor).
  A(A &&t)
  {
    // Move the data from object t to *this.
  }
  
  // The copy assignment operator always:
  // * has a single parameter of type const A &,
  // * returns an lvalue reference to *this.
  A &
  operator=(const A &source)
  {
    m_name = source.m_name;
    cout << "copy-assign: " << m_name << '\n';
    return *this;
  }  
};

int
main()
{
  A a("Hello!");
  // Calls the copy constructor.
  A b(a);
  // Calls the copy assignment operator.
  b = a;
}

struct T
{
};
