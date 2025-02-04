#include <iostream>

int
main()
{
  auto s = 0 <=> 1;
  std::cout << s < 0;
}
