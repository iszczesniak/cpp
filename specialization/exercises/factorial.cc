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

int main()
{
  cout << factorial<5>() << endl;
}
