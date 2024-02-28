#include <iostream>

struct A
{
  static volatile long i;

  A()
  {
    ++i;
  }

  A(const A &)
  {
    ++i;
  }
};

volatile long A::i = 0;


A foo(A)
{
  return A();
}

int
main()
{
  for(long i = 0; i < 1000000000; ++i)
    A a = foo(A());

  std::cout << A::i << std::endl;
}
