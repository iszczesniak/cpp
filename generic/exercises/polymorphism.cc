#include "timer.hpp"

#include <iostream>

volatile long x, y;
const long num = 1000000;

struct A
{
  virtual void foo() const
  {
    ++x;
  }
};

struct B: A
{
  void foo() const override
  {
    ++y;
  }
};

void foo(const A &)
{
  ++x;
}

void foo(const B &)
{
  ++y;
}

template <typename T>
void loop(const T &o)
{
  for(long i = 0; i < num; ++i)
    foo(o);
}

int
main()
{
  volatile bool flag = true;

  {
    timer t("dynamic polymorphism");
    const A *p;

    if (flag)
      p = new A();
    else
      p = new B();

    for(long i = 0; i < num; ++i)
      p->foo();

    delete p;
  }

  {
    timer t("static polymorphism");

    if (flag)
      loop(A());
    else
      loop(B());
  }

  std::cout << "x = " << x << std::endl;
  std::cout << "y = " << y << std::endl;
}
