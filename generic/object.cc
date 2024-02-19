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
  void foo() const override
  {
    std::cout << "B\n";
  }
};

void
foo(const A &a)
{
  std::cout << "Function foo: ";
  a.foo();
  std::cout << std::endl;
}

int
main()
{
  // foo(1);
  foo(A());
  foo(B());
}
