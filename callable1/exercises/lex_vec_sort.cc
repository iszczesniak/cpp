#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main()
{
  vector<pair<string, int>> v = {{"Joe", 2}, {"Boe", 2}, {"Shmoe", 1}};

  sort(v.begin(), v.end(), [](const pair<string, int> &i,
                              const pair<string, int> &j)
  {
    return tie(i.second, i.first) < tie(j.second, j.first);
  });

  for(const auto &e: v)
    std::cout << e.first << ", " << e.second << "\n";
}
