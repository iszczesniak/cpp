#include <iostream>
#include <string>

struct A
{
  // We need to make these member fields volatile or otherwise they
  // will get optimized out.  Remove volatile and compile with -O3.
  static volatile long i;
  volatile std::string m_txt = "Hello!";

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
  for(long i = 0; i < 100000000; ++i)
    A a = foo(A());

  std::cout << A::i << std::endl;
}
