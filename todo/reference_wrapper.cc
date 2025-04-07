#include <cassert>
#include <iostream>
#include <functional>

int
main()
{
  int x = 1, y = 2;

  // We cannot have a C-array of references.
  // int &t[] = {x, y};

  using rw2i = std::reference_wrapper<int>;
  rw2i t[] = {x, y};
  t[1].get() = 20;
  assert(t[1] == y);
  t[1] = std::ref(x);
  assert(t[1] == x);
}
