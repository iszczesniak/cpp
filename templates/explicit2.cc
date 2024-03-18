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
  // The constructor is templated, even though the struct is not.
  template <typename T>
  B(T t)
  {
    cout << "ctor B: " << t << endl;
  }
};

template <typename T, typename A>
T
factory(A a)
{
  return T(a);
}

int
main()
{
  // Just as for std::make_unique.
  factory<A>(1);
  factory<B>(1.1);
  factory<B>("Hello World!");
}
