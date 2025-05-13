#include "my_weak_ptr.hpp"

#include <cassert>
#include <iostream>

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

int
main()
{
  my_unique_ptr<A> up(new A);
  // my_unique_ptr<A> up2 = up;
  my_unique_ptr<A> up2 = move(up);

  my_unique_ptr<A> up3;
  // up3 = up2;
  up3 = std::move(up2);

  my_shared_ptr<A> sp = move(up3);

  {
    my_shared_ptr<A> sp2 = sp;
    my_shared_ptr<A> sp3;
    sp3 = sp2;

    my_shared_ptr<A> sp4 = move(sp);
    sp3 = move(sp2);

    my_weak_ptr<A> wp = sp3;
    my_weak_ptr<A> wp2 = wp;
    my_weak_ptr<A> wp3(move(wp));
    my_weak_ptr<A> wp4;
    wp4 = wp2;

    my_shared_ptr<A> sp5 = wp4;
  }

  std::cout << "Bye!\n";
}
