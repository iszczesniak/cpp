#include <iostream>
#include <vector>

using namespace std;

template <template<typename> typename F = less,
          template<typename> typename C,
          typename T>
void
battery(T e, const C<T> &c, F<T> f = {})
{
  for(const auto &i: c)
    cout << f(i, e) << endl;

  cout << endl;
}

int
main()
{
  cout << boolalpha;
  
  vector c = {8, 3, 7, 9, 2, 4, 8, 5};

  battery(5, c);
  battery(5, c, greater<int>{});
  battery<plus>(5, c);

  // Error: .5 is not of the integer type.
  // battery(.5, c, less<int>{});

  // Error: double is not the integer type.
  // battery(5, c, less<double>{});
}
