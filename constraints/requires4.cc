#include <array>
#include <string>
#include <utility>

using namespace std;

template <typename C> requires requires {typename C::iterator;}
void
iterate(C &t) requires requires
  {
    {t.begin()} -> same_as<typename C::iterator>;
  }
{
}

int
main()
{
  array a{1, 2};
  iterate(a);

  std::string s("Hello World!");
  iterate(s);

  pair p{1, .1};
  // Error: pair doesn't have the iterator type.
  // iterate(p);
}
