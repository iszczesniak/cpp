#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int
main()
{
  vector v{3, 1, 2};
  sort(v.begin(), v.end());
  for(const auto &e: v)
    cout << e << endl;
}
