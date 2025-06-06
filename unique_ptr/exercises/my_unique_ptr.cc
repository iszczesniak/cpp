#include "my_unique_ptr.hpp"

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
  // For a non-const object.
  {
    my_unique_ptr<A> up(new A);
    // my_unique_ptr<A> up1 = up;
    my_unique_ptr<A> up2 = std::move(up);

    my_unique_ptr<A> up3;
    // up3 = up2;
    up3 = std::move(up2);

    assert(!up);
    assert(up3);
    (*up3).foo();
    up3->foo();
  }

  // For a const object.
  {
    my_unique_ptr<const A> up(new A);
    // my_unique_ptr<A> up1 = up;
    my_unique_ptr<const A> up2 = std::move(up);

    my_unique_ptr<const A> up3;
    // up3 = up2;
    up3 = std::move(up2);

    assert(!up);
    assert(up3);
    (*up3).foo();
    up3->foo();
  }
}
