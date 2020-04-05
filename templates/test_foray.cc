#include <array>
#include <iostream>

int
main()
{
  std::array a{1, 2};
  for(auto e: a)
    std::cout << e;
}
