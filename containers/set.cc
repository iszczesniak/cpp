#include <iostream>
#include <set>

using namespace std;

int
main()
{
  set<int> s = {3, 1, 2};

  for(auto &e: s)
    cout << e << endl;

  // This would not compile, because we cannot modify the elements.
  // for(auto &e: s)
  //   cout << ++e << endl;
}
