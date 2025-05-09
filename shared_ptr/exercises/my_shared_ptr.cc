#include "my_unique_ptr.hpp"
#include "my_shared_ptr.hpp"

#include <cassert>
#include <iostream>
#include <utility>

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

  void foo() const
  {
    cout << "Hello World!\n";
  }
};

int
main()
{
  my_unique_ptr<A> up(new A);
  my_shared_ptr<A> sp = move(up);

  {
    my_shared_ptr<A> sp1 = sp;
    my_shared_ptr<A> sp2;
    sp2 = sp1;
    my_shared_ptr<A> sp3(move(sp1));
    my_shared_ptr<A> sp4;
    sp4 = move(sp2);
  }

  assert(sp);
  (*sp).foo();
  sp->foo();

  // We move the ownership to a temporary.
  my_shared_ptr<A>(move(sp));

  assert(!sp);

  cout << "Bye!\n";
}
