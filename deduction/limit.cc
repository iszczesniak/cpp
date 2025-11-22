#include <array>
#include <iostream>
#include <vector>

template <typename T>
void foo(std::vector<T> v)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int
main()
{
  std::initializer_list l = {1, 2, 3};
  std::vector v = l;
  // foo(l);
}
