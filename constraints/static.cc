#include <concepts>
#include <iostream>
#include <type_traits>

using namespace std;

struct A
{
  virtual void hello() const
  {
    cout << __PRETTY_FUNCTION__ << endl;
  }
};

struct B: A
{
  void hello() const override
  {
    cout << __PRETTY_FUNCTION__ << endl;
  }
};

struct C
{
};

void
goo(const A &)
{
  cout << "A\n";
}

void
goo(const B &)
{
  cout << "B\n";
}

// For objects of any class derived from A.
void
foo1(const A &a)
{
  cout << __PRETTY_FUNCTION__ << endl;
  // This call has to be virtual.
  a.hello();
  goo(a);
}

// For objects of any class that has the hello function.
template <typename T>
void
foo2(const T &t)
{
  cout << __PRETTY_FUNCTION__ << endl;
  // This call does not have to be virtual.
  t.hello();
  goo(t);
}

// For objects of any class derived from A.
template <typename T> requires std::derived_from<T, A>
void
foo3(const T &t)
{
  cout << __PRETTY_FUNCTION__ << endl;
  // This call does not have to be virtual.
  t.hello();
  goo(t);
}

int
main()
{
  A a;
  B b;
  C c;

  foo1(a);
  foo1(b);
  // Error with a clear message from the interface.
  // foo1(c);

  foo2(a);
  foo2(b);
  // Error with an ugly message from the implementation.
  // foo2(c);

  foo3(a);
  foo3(b);
  // Error with a clear message from the interface.
  // foo3(c);
}
