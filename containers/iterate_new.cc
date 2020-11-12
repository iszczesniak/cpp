#include <iostream>
#include <vector>
#include <utility>

int main()
{
  std::vector<int> a = {1, 2, 3};

  for(auto &e: a)
    std::cout << e << std::endl;

  // We can modify the elements, because we use them through a
  // non-const reference of type: auto &
  for(auto &e: a)
    std::cout << ++e << std::endl;

  // This would not compile, because we refer to the elements through
  // a const reference: const auto &

  // for(const auto &e: a)
  //   std::cout << ++e << std::endl;

  // We could also iterate through a non-const container and reference
  // the elements with a const reference, becasue we refer to the
  // non-const container with a const reference.

  for(auto &e: std::as_const(a))
    std::cout << e << std::endl;
  
  // This would not compile, because we're trying to modify elements
  // of container referred to with a const reference.

  // for(auto &e: std::as_const(a))
  //   std::cout << ++e << std::endl;
}
