#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <vector>

using namespace std;

int
main()
{
  map<int, string> m = {{1, "Alice"}, {2, "Bob"}};
  vector<std::reference_wrapper<const string>> names;

  for(const pair<int, string> &e: m)
    names.push_back(std::ref(e.second));

  for(const auto &e: names)
    cout << e.get() << endl;
}
