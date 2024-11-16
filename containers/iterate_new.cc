#include <iostream>
#include <vector>
#include <utility>

int main()
{
  std::vector<int> v = {1, 2, 3};

  for(auto &e: v)
    std::cout << e << std::endl;

  // We can modify the elements, because we use them through a
  // non-const reference of type: auto &
  for(auto &e: v)
    std::cout << ++e << std::endl;

  // Here we iterate with a const reference.
  for(const auto &e: v)
    std::cout << e << std::endl;

  // This would not compile, because we refer to the elements through
  // a const reference: const auto &

  // for(const auto &e: v)
  //   std::cout << ++e << std::endl;

  // We could also iterate through a non-const container and reference
  // the elements with a const reference, becasue we refer to the
  // non-const container with a const reference.

  for(auto &e: std::as_const(v))
    std::cout << e << std::endl;
  
  // This would not compile, because we're trying to modify elements
  // of container referred to with a const reference.

  // for(auto &e: std::as_const(v))
  //   std::cout << ++e << std::endl;
}
