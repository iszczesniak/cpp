#include <algorithm>
#include <iostream>

using namespace std;

struct A
{
  int id;
  A(int id): id(id)
  {
  }
};

int
main()
{
  vector v{3, 1, 2};
  sort(v.begin(), v.end());
  for(const auto &e: v)
    cout << e << endl;
}
