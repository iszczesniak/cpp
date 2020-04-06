#include <iostream>

struct A
{
  virtual void fun() const
  {
    std::cout << "A\n";
  }
};

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
  a.foo();
}

int
main()
{
  foo(A());
  foo(B());
}
