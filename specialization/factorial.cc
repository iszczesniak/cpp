#include <iostream>

using namespace std;

template<int N>
constexpr int factorial()
{
  return N * factorial<N - 1>();
}

template<>
constexpr int factorial<0>()
{
  return 1;
}

template<typename T, T N>
constexpr T factorial()
{
  if constexpr (N)
    return N * factorial<N - 1>();
  else
    return 1;
}

int main()
{
  cout << factorial<5>() << endl;
  cout << factorial<int, 5>() << endl;
  cout << factorial<long long, 20>() << endl;
}
