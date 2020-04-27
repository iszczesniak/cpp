#include <iostream>

using namespace std;

template <typename A>
void
foo(A a)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  // The following could not compile: when instantiated in the
  // example, "a" cannot be used in the foreach loop, because it's of
  // type "int *".
  //
  // for(auto &e: *a)
  //   cout << e << endl;

  cout << a[0] << endl;
  cout << a[1] << endl;
  cout << a[2] << endl;
}

void
goo(int *a)
{
  // for(auto &e: *a)
  //   cout << e << endl;

  cout << a[0] << endl;
  cout << a[1] << endl;
  cout << a[2] << endl;

  // This compiles without an error or a warning, because the compiler
  // has no clue we're using a table of three elements.
  cout << a[3] << endl;
}

int
main()
{
  // Type of a is: int[3]
  int a[] = {1, 2, 3};
  foo(a);
  goo(a);
}
