#include <algorithm>
#include <iostream>
#include <functional>

using namespace std;

struct A
{
  int id;
  A(int id): id(id)
  {
  }

  bool
  operator < (const A &a) const
  {
    return this->id < a.id;
  }
};

int
main()
{
  vector v{A(3), A(1), A(2)};
  sort(v.begin(), v.end(), std::less<A>{});
  for(const auto &e: v)
    cout << e.id << endl;
}
