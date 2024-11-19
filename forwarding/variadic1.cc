#include <memory>
#include <utility>
#include <vector>

using namespace std;

template <typename T, typename ... P>
auto
my_make_unique(P &&...p)
{
  return unique_ptr<T>(new T{std::forward<P>(p)...});
}

int
main()
{
  auto p = my_make_unique<std::vector<int>>(1, 2, 3);
}
