#include <iostream>
#include <utility>

int
main()
{
  int x = 1;
  double y = .2;
  std::pair<int &, double &> p{x, y};
  std::cout << p.first << p.second << std::endl;
}
