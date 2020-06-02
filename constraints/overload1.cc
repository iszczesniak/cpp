#include <concepts>
#include <iostream>

using namespace std;

template <unsigned I, typename T> requires integral<T>
void
divide(T x)
{
  cout << "divide: integral" << endl;
}

template <unsigned I, typename T> requires (I == 0) && integral<T>
void
divide(T x)
{
  cout << "divide: don't divide integrals by 0" << endl;
}

int
main()
{
  int x = 1;
  divide<0>(x);
  divide<1>(x);
}
