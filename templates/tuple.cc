#include <iostream>
#include <tuple>

using namespace std;

int
main()
{
  tuple t{1, 2};
  cout << get<0>(t) << get<1>(t);
}
