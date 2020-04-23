#include <iostream>
#include <iterator>

using namespace std;

int
main()
{
  int a[] = {3, 1, 2};
  sort(begin(a), end(a));
  for(const auto &e: v)
    cout << e << endl;
}
