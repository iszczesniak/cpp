#include <iostream>

// This is an example for polymorphism.

struct A
{
  void foo()
  # virtual void foo()
  {
    std::cout << "A\n";
  }
};

struct B: A
{
  void foo()
  {
    std::cout << "B\n";
  }
};

void
foop(A *a)
{
  a->foo();
}

void
foor(A &a)
{
  a.foo();
}

int
main()
{
  A *p = new B();
  foop(p);
  delete p;

  B b;
  foor(b);
}
