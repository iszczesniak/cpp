#include <memory>
#include <vector>

using namespace std;

template <typename T>
auto
my_make_unique(auto &&...p)
{
  return unique_ptr<T>(new T{forward<decltype(p)>(p)...});
}

int
main()
{
  auto p = my_make_unique<std::vector<int>>(1, 2, 3);
}
