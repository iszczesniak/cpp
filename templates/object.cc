#include <iostream>

struct A
{
  virtual void foo() const
  {
    std::cout << "A\n";
  }
};

// Type B must derive from the base class.
struct B: A
{
  void foo() const
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
  // foo(1);
  foo(A());
  foo(B());
}
