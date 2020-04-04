#include <array>
#include <iostream>

int
main()
{
  std::array<int, 2> a{1, 2};
  for(auto e: a)
    std::cout << e;
}
