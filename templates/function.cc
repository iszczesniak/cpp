#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

template <typename T>
void
print(const T &t)
{
  static_assert(std::is_integral<T>::value);
  cout << t << endl;
}

template <int N>
void
print()
{
    cout << N << endl;
}

template <typename T, template<typename> typename C>
void
foo(T a)
{
  C<T> c;
}

template <typename T>
using my_vec = std::vector<T>;

int
main()
{
  print(1);
  // print<int>(0.5);
  // print<double>(0.5);
  // print("Hello!");
  // print(string("Hello!"));
  print<100>();
  
  foo<int, my_vec>(1);
}
