#include <iostream>

using namespace std;

int
main()
{
  // C-style array.
  int a[] = {1, 2, 3};

  // The same as: int *i = a;
  auto i = std::begin(a);
  cout << *i << endl;
  cout << *(i + 2) << endl;
  ++i;
  cout << *(i - 1) << endl;
  --i;
  cout << std::boolalpha << (i == std::end(a)) << endl;
  i += 3;
  cout << std::boolalpha << (i == std::end(a)) << endl;
}
