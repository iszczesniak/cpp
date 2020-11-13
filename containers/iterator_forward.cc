#include <deque>
#include <list>

using namespace std;

int
main()
{
  forward_list<int> a = {1, 2, 3};

  auto i = std::begin(a);
  cout << *i << endl;
  // That would not compile.
  // cout << *(i + 2) << endl;
  ++i;
  // That would not compile.
  // cout << *(i - 1) << endl;
  // That would not compile.
  // --i;
  cout << std::boolalpha << (i == std::end(a)) << endl;
  // That would not compile.
  // i += 3;
  cout << std::boolalpha << (i == std::end(a)) << endl;
}
