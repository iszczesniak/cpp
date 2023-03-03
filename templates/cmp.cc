#include <iostream>
#include <vector>

template <typename T, template<typename> typename C, typename F>
void
cmp(T e, const C<T> &c, F f)
{
  for(const auto &i: c)
    std::cout << f(i, e) << std::endl;
}

int
main()
{
  std::vector c = {8, 3, 7, 9, 2, 4, 8, 5};
  cmp(5, c, std::less<int>{});
}
