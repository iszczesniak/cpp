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

  // Here the managed data exist.
  {
    shared_ptr<A> sp2(wp);
    sp2->saysomething();
    assert(sp2 != nullptr);
  }

  // Flush the managed data.
  sp.reset();

  // Here the managed data is gone.
  {
    shared_ptr<A> sp2 = wp.lock();
    assert(sp2 == nullptr);
  }
}
