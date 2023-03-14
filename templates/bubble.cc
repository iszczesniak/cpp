#include <iostream>
#include <iterator>
#include <list>
#include <vector>

using namespace std;

// The bubble sort requires only a forward iterator.
template <typename I, typename F>
void bubble(I i1, I i2, F f)
{
  if (i1 != i2)
    while(i1 != --i2)
      for(auto i = i1; i != i2; ++i)
        if (!f(*i, *(i+1)))
          std::swap(*i, *(i+1));  
}

bool cmp(const int &a, const int &b)
{
  return a > b;
}

int
main()
{
  int t[] = {1, 5, 3, 2};
  bubble(begin(t), end(t), less<int>{});
  for(const auto &e: t)
    cout << e << '\n';

  vector v = {1, 5, 3, 2};
  bubble(begin(v), end(v), cmp);
  for(const auto &e: v)
    cout << e << '\n';

  cout << "*****************************\n";
  
  // list fl = {3, 4, 2, 0};
  // bubble(begin(fl), end(fl), cmp);
  // for(const auto &e: fl)
  //   cout << e << '\n';
}
