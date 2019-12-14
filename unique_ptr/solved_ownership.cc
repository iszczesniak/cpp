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

auto // C++14
factory()
{
  auto p = make_unique<A>();

  return p; // Return value optimization.
}

void
stash(unique_ptr<A> p)
{
  static unique_ptr<A> stash;
  stash = move(p);
}

int
main()
{
  auto p = factory();
  stash(move(p));
}
