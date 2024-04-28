#include <algorithm>
#include <iterator>
#include <list>
#include <string>
#include <vector>

template <typename C, typename I>
concept comparator =
  std::invocable<C, std::iter_const_reference_t<I>,
                 std::iter_const_reference_t<I>>;

template <std::random_access_iterator I, comparator<I> C>
void
mysort(I i1, I i2, C &&c)
{
  std::sort(i1, i2, std::forward<C>(c));
}

bool
foo(const int &a, const int &b)
{
  return a < b;
}

bool
goo(const std::string &a, const std::string &b)
{
  return a < b;
}

int
main()
{
  std::vector v = {3, 1, 2};
  mysort(v.begin(), v.end(), foo);
  // mysort(v.begin(), v.end(), goo);

  std::list l = {3, 1, 2};
  // mysort(l.begin(), l.end(), foo);
}
