#include <iostream>
#include <vector>

int main()
{
  std::vector<int> a = {1, 2, 3};
  for(const auto &e: a)
    std::cout << e << std::endl;
}
