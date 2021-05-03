#include <cassert>
#include <set>
#include <vector>

int
main()
{
  std::vector<int> vi = {1};
  std::set<int> s = {1};

  // We can initialize a non-const reference to a vector element.
  int &a = *vi.begin();

  // We cannot initialize a non-const reference to a set element.
  // int &b = *s.begin();

  // The reference has to be const.
  const int &c = *s.begin();

  // It's best to let the compiler figure out the right type.  As part
  // of the type deduction, e becomes a const reference.
  auto &d = *vi.begin();
  auto &e = *s.begin();

  std::vector<bool> vb = {true};
  // auto &f = *vb.begin();
  auto &&f = *vb.begin();
}
