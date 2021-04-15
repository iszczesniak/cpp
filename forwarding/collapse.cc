#include <iostream>
#include <type_traits>

using namespace std;

template<typename T>
struct A
{
  using type = T &&;
};

int
main()
{
  cout << std::boolalpha;

  using lt = int &;
  using rt = int &&;

  using typ1 = lt &&;
  cout << is_same_v<int &, typ1> << endl;

  using typ2 = rt &&;
  cout << is_same_v<int &&, typ2> << endl;

  cout << is_same_v<int &, typename A<lt>::type> << endl;
  cout << is_same_v<int &&, typename A<rt>::type> << endl;
}
