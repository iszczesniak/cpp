#include <iostream>
#include <string>

using namespace std;

struct A
{
  string m_name;

  A()
  {
    cout << "default-ctor" << endl;
  }

  A(const string &name): m_name(name)
  {
    cout << "direct-ctor: " << m_name << endl;
  }

  A(const A &a): m_name(a.m_name)
  {
    cout << "copy-ctor: " << m_name << endl;
  }

  ~A()
  {
    cout << "dtor: " << m_name << endl;
  }
};

int main()
{
  // That's a function declaration, though in the legacy C++ it used
  // to mean the default initialization of object "foo".
  A foo();

  // The equivalent ways of default initialization.
  {
    A a;
    A b{};
    A c = A();
    A d = A{};
    A e(A{});
    A f{A()};

    // Acceptable and interesting, but we don't code like that.
    A g = A(A());
    A h = A{A{}};
  }

  // The equivalent ways of direct (with arguments) initialization.
  {
    A a("a");
    A b{"b"};
    A c = A("c");
    A d = A{"d"};
    A e(A{"e"});
    A f{A("f")};

    // Acceptable and interesting, but we don't code like that.
    A g = A(A("e"));
    A h = A{A{"f"}};
  }
}
