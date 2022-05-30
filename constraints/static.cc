#include <iostream>
#include <type_traits>

using namespace std;

struct A
{
  void
  hello() const
  {
    cout << "Hello ";
  }
};

struct B: A
{
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
  a.hello();
  goo(a);
}

// For objects of any class that has the hello function.
template <typename T>
void
foo2(const T &t)
{
  cout << __PRETTY_FUNCTION__ << endl;
  t.hello();
  goo(t);
}

// For objects of any class derived from A.
template <typename T> requires std::is_base_of_v<A, T>
void
foo3(const T &t)
{
  cout << __PRETTY_FUNCTION__ << endl;
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
  // Error, but with a clear error message from the interface.
  // foo1(c);

  foo2(a);
  foo2(b);
  // Error, but with an ugly error message from the implementation.
  // foo2(c);

  foo3(a);
  foo3(b);
  // Error, but with a clear error message from the interface.
  // foo3(c);    
}
