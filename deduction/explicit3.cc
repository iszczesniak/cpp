#include <iostream>

using namespace std;

struct A
{
  A(int i)
  {
    cout << "ctor A: " << i << endl;
  }
};

struct B
{
  template <typename T>
  B(T t)
  {
    cout << "ctor B: " << t << endl;
  }
};

template <typename A, typename T>
T
factory(A a)
{
  return T(a);
}

int
main()
{
  factory<int, A>(1);
  factory<double, B>(1.1);
  factory<const char *, B>("Hello World!");
}
