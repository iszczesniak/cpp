#include <iostream>

struct A
{
};

// B doesn't have to derive from a base class.
struct B
{
};

void foo(const int &i)
{
  std::cout << i;
}

void foo(const A &)
{
  std::cout << "A\n";
}

void foo(const B &)
{
  std::cout << "B\n";
}

int
main()
{
  // foo(1);
  foo(A());
  foo(B());
}
