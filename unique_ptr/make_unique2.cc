#include <memory>

struct A
{
};

A *
factory()
{
  return new A();
}

int
main()
{
  A *p = factory();
  delete p;
}
