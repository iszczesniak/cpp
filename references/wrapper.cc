#include <iostream>
#include <vector>

using namespace std;

int
main()
{
  int x = 1, y = 2;

  reference_wrapper<int> r(x);
  r = reference_wrapper<int>(y);
  r = 20;
  cout << y;
}
