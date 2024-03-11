#include <iostream>

using namespace std;

template <typename A>
void
foo(A *a)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  for(auto &e: *a)
    cout << e << endl;

  // Should the following compile for an array of three or less?  GCC
  // gives no warning, but clang does.
  cout << a[3] << endl;
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
