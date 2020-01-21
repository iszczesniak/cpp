#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

using namespace std;

struct A
{
  string m_text;

  A(const string &text): m_text(text)
  {
    cout << "ctor: " << m_text << endl;
  }

  ~A()
  {
    cout << "dtor: " << m_text << endl;
  }
};

int main (void)
{
  // sp takes the ownership.
  shared_ptr<A> sp(new A("A1"));
  assert(sp);

  // We make sp manage a new object.  A1 is destroyed.
  sp.reset(new A("A2"));

  {
    // We copy-initialize the ownership.
    shared_ptr<A> sp2(sp);
    assert(sp);
    assert(sp2);

    shared_ptr<A> sp3;
    // We copy-assign the ownership.
    sp3 = sp2;
    assert(sp2);
    assert(sp3);

    // Even though sp2 and sp3 go out of scope, A2 will not be
    // destroyed, because it's still being managed by sp.
  }

  {
    // We move-initialize the ownership.
    shared_ptr<A> sp2(move(sp));
    assert(!sp);
    assert(sp2);

    shared_ptr<A> sp3;
    // We move-assign the ownership.
    sp3 = move(sp2);
    assert(!sp2);
    assert(sp3);

    // A2 is destroyed, because sp3 goes out of scope.
  }

  // We can't release the managed data from being managed, as we are
  // able to do with unique_ptr, because we can't preempt (strip)
  // other shared_ptr objects of their ownership.

  // sp.release();

  // If we want to reset a pointer, we can use the reset function.
  sp.reset();
}
