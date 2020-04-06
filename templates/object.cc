#include <iostream>

struct A
{
  virtual void fun() const
  {
    std::cout << "A\n";
  }
};

// Type B must derive from the base class.
struct B: A
{
  void fun() const
  {
    std::cout << "B\n";
  }
};

void
foo(const A &a)
{
  a.fun();
}

int
main()
{
  foo(A());
  foo(B());
}
