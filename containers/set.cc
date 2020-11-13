#include <iostream>
#include <set>

using namespace std;

int
main()
{
  // A compiler can deduce the type of the elements stored in the set.
  // Equivalent to: set<int> s = {3, 1, 2};
  set s = {3, 1, 2};

  for(auto &e: s)
    cout << e << endl;

  // This would not compile, because we cannot modify the elements.
  // for(auto &e: s)
  //   cout << ++e << endl;

  multiset ms = {1, 2, 3, 1, 2, 3};

  for(auto &e: ms)
    cout << e << endl;
}
