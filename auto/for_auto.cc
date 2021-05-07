#include <iostream>
#include <map>
#include <string>

using namespace std;

int
main()
{
  map<int, string> m = {{1, "Hello"}, {2, "World"}};
  map<int, const string &> mr;

  for(pair<const int, string> &e: m)
    mr.insert(make_pair(e.first, e.second));

  for(auto &e: mr)
    cout << e.first << ", " << e.second << endl;
}
