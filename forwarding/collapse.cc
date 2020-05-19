#include <iostream>
#include <type_traits>

using namespace std;

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
}
