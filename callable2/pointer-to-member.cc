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

  void foo()
  {
    cout << __PRETTY_FUNCTION__ << " for " << m_name << endl;
  }

  void goo()
  {
    cout << __PRETTY_FUNCTION__ << " for " << m_name << endl;
  }
};

int
main()
{
  A a("a"), b("b");

  // A pointer to any member function of A with the defined interface.
  void (A::* p1)() = &A::foo;
  // It's better to let the compiler deduce the type.
  auto p2 = &A::goo;
  // Make sure the types are the same.
  static_assert(std::is_same_v<decltype(p1), decltype(p2)>);

  (a.*p1)();
  (b.*p1)();
  (a.*p2)();
  (b.*p2)();

  // We can also store a pointer to a member function with an object
  // to call.
  std::function<void ()> f = std::bind(p1, a);
  f();
  f = std::bind(p2, b);
  f();
}
