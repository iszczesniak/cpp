#include <iostream>

using namespace std;

template <typename A>
void
foo(A *a)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  for(auto &e: *a)
    cout << e << endl;

  // I thought the following should not compile, but it does.  I hoped
  // to get an error or at least a warning, because the compiler knows
  // the function is instantiated for this type: int (&)[3]

  // cout << a[3] << endl;
}

void
goo(int (*a)[3])
{
  for(auto &e: *a)
    cout << e << endl;

  // cout << a[3] << endl;
}

int
main()
{
  int a[] = {1, 2, 3};
  foo(&a);
  goo(&a);
}
