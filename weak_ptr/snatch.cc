#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

int
main()
{
  auto sp = make_shared<int>();
  weak_ptr<int> wp(sp);

  // Here the managed data exist.
  {
    shared_ptr<int> sp(wp);
    assert(sp);
  }

  // Here the managed data exist.
  {
    shared_ptr<int> sp = wp.lock();
    assert(sp);
  }

  // Flush the managed data.
  sp.reset();

  // Here the managed data is gone.
  try
    {
      shared_ptr<int> sp(wp);
    }
  catch (std::bad_weak_ptr &)
    {
      cout << "Caught a std::bad_weak_ptr.\n";
    }

  // Here the managed data is long gone.
  {
    shared_ptr<int> sp = wp.lock();
    assert(!sp);
  }
}
