#include <iostream>

struct A
{
};

std::ostream &
operator << (std::ostream &os, const A &)
{
  os << "A";
  return os;
}

// B doesn't have to derive from a base class.
struct B
{
};

std::ostream &
operator << (std::ostream &os, const B &)
{
  os << "B";
  return os;
}

template <typename T>
void foo(const T &t)
{
  std::cout << "Function foo: ";
  std::cout << t << std::endl;
}

int
main()
{
  foo(1);
  foo(A());
  foo(B());
}
