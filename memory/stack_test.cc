#include <iostream>

using namespace std;

void
foo(long int x)
{
  int y = x;
  cout << y << endl;
  foo(++y);
}

int main()
{
  foo(0);
}
