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
  cout << is_same<int &, typ1>::value << endl;

  using typ2 = rt &&;
  cout << is_same<int &&, typ2>::value << endl;

  cout << is_same<int &&, typename A<int>::type>::value << endl;
  cout << is_same<int &, typename A<int &>::type>::value << endl;
  cout << is_same<int &&, typename A<int &&>::type>::value << endl;
}
