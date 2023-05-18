#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool
cmp(const int &a, const int &b)
{
  return a > b;
}

int
main()
{
  vector v{3, 1, 2};
  sort(v.begin(), v.end(), cmp);
  for(const auto &e: v)
    cout << e << endl;
}
