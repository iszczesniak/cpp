#include <iostream>
#include <utility>

using namespace std;

void
foo(int &)
{
  cout << "foo dla l-wartości\n";
}

void
foo(int &&)
{
  cout << "foo dla r-wartości\n";
}

int
main()
{
  int x = 1;
  foo(forward<int &>(x));
  foo(forward<int>(x));
}
