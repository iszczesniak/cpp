#include "weight.hpp"

#include <iostream>

using namespace std;

template <typename T>
struct A: weight<T>
{
};

int main()
{
  const A<int> a1{0}, b1{1};
  cout << a1 << '\n' << b1 << '\n';
  // Does not compile.
  // get_weight(a1) += 1;

  A<double> a2{0.1}, b2{1.1};
  get_weight(a2) += get_weight(b2) += 1;
  cout << a2 << '\n' << b2 << '\n';
}
