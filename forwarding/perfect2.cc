#include <iostream>
#include <utility>

using namespace std;

template <typename T>
void
g(int &)
{
  cout << __PRETTY_FUNCTION__ << endl;
  static_assert(std::is_same_v<T, int &>);
}

template <typename T>
void
g(const int &)
{
  cout << __PRETTY_FUNCTION__ << endl;
  static_assert(std::is_same_v<T, const int &>);
}

template <typename T>
void
g(int &&)
{
  cout << __PRETTY_FUNCTION__ << endl;
  static_assert(std::is_same_v<T, int &&>);
}

template<typename C, typename T>
void
f(T &&t)
{
  cout << __PRETTY_FUNCTION__ << endl;
  // g<C>(t);
  g<C>(forward<T>(t));
}

int main()
{
  // Test "int &"
  int x;
  g<int &>(x);
  f<int &>(x);

  // Test "const int &"
  const int &y = 1;
  g<const int &>(y);
  f<const int &>(y);

  // Test "int &&"
  g<int &&>(1);
  f<int &&>(1);
}
