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
  // * has the return type A &.
  A &
  A(A &&t): m_name(move(source.m_name))
  {
    // Move the data from object t to *this.
    cout << "move-ctor: " << m_name << '\n';
    return *this;
  }
};

int
main()
{
  A a("Hello!");
  // Calls the copy constructor.
  A b(a);
  // Calls the move constructor.
  A c(A("test"));
  // Calls the move constructor.
  A d(move(a));
}
