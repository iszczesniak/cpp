#include <iostream>

void fun(const A &)
{
  std::cout << "A\n";
}

void fun(const B &)
{
  std::cout << "B\n";
}

template <typename T>
void
foo(const T &a)
{
  foo(a);
}

int
main()
{
  foo(A());
  foo(B());
}
