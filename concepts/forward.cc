#include <iostream>
#include <utility>

using namespace std;

template <typename T>
concept incr = requires (T t) {++t;};

void
g(int &)
{
  cout << "l-value\n";
}

void
g(int &&)
{
  cout << "r-value\n";
}

void
f(incr auto &&x)
{
  g(forward<decltype(x)>(x));
}

int
main()
{
  int x = 1;
  f(x);
  f(1);
}
