#include <cassert>

int &
singleton()
{
  static int i = 0;
  return i;
}

int main()
{
  auto i = singleton();
  i = 1;
  assert(singleton() == 0);
  
  decltype(auto) r = singleton();
  r = 1;
  assert(singleton() == 1);
}
