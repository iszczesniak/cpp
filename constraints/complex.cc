#include <iostream>
#include <type_traits>

using namespace std;

template <unsigned I, typename T>
  requires (I != 0) && is_arithmetic_v<T>
T
divide(T t)
{
  return t / I;
}

int
main()
{
  cout << divide<2>(4) << endl;
  // cout << divide<0>(4) << endl;
  // cout << divide<2>("Hi!") << endl;
}
