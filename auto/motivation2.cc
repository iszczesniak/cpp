#include <cassert>
#include <set>
#include <vector>

int
main()
{
  std::vector<int> v = {1};
  std::set<int> s = {1};

  // We can initialize a non-const reference to a vector element.
  int &a = *v.begin();

  // We cannot initialize a non-const reference to a set element.
  // int &b = *s.begin();

  // The reference has to be const.
  const int &c = *s.begin();

  // It's best to let the compiler figure out the right type.
  auto &d = *v.begin();
  auto &e = *s.begin();

  std::vector<bool> v2 = {true};
  // This, however, doesn't compile, and I don't know why.
  // auto &f = *v2.begin();

  // This compiles, and works, but it's overcomplicated.
  decltype(*v2.begin()) f = *v2.begin();
  f = false;
  assert(f == false);
}
