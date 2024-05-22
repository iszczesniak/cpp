#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

struct A
{
  A()
  {
    cout << "ctor\n";
  }

  ~A()
  {
    cout << "dtor\n";
  }
};

shared_ptr<A>
factory()
{
  static weak_ptr<A> wp;

  auto sp = wp.lock();

  if (!sp)
    wp = sp = make_shared<A>();

  return sp;
}

int
main()
{
  factory();
  auto sp1 = factory();
  auto sp2 = factory();
  assert(sp1 == sp2);
}
