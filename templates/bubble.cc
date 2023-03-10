#include <iostream>
#include <iterator>
#include <forward_list>

using namespace std;

// The bubble sort requires only a forward iterator.
template <typename I, typename F>
void bubble(I i1, I i2, F f)
{
  while(i1 != i2)
    for(auto j = ++i1; j != i2; ++j)
      if (f(*i1, *j))
        std::swap(*i1, *j);  
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

  cout << "*****************************\n";
  
  forward_list fl = {3, 4, 2, 0};
  bubble(begin(fl), end(fl), cmp);
  for(const auto &e: fl)
    cout << e << '\n';
}
