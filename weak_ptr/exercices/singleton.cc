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
singleton()
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
  singleton();
  auto sp1 = singleton();
  auto sp2 = singleton();
  assert(sp1 == sp2);
}
