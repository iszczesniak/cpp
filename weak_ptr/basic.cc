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

  void
  saysomething()
  {
    cout << "Hi!\n";
  }

  ~A()
  {
    cout << "dtor\n";
  }
};

int
main()
{
  auto sp = make_shared<A>();
  weak_ptr<A> wp(sp);

  // The assert below doesn't compile, because it would suggest the
  // same semantics as for the unique and shared pointers, that we've
  // got the managed data, and can use them (which is wrong for the
  // weak pointer).

  // assert(wp);

  // Instead we can use function 'expired' of the weak pointer, which
  // should alert us of a special semantics.
  assert(!wp.expired());

  // Here the managed data exist.
  {
    shared_ptr<A> sp2(wp);
    sp2->saysomething();
    assert(sp2);
  }

  // Flush the managed data.
  sp.reset();

  // Here the managed data is gone.
  assert(wp.expired());
}
