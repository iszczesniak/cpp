#include <iostream>
#include <utility>
#include <tuple>
#include <vector>

int main()
{
  int x = 1;

  std::pair<int &, int &> p(x, x);
  p.second = 2;

  std::cout << "x = " << x << std::endl;

  // BŁĄD: elementy pary muszą być zainicjalizowane.
  // std::pair<int &, int &> p2;

  std::tuple<int &, int &, int &> t(x, x, x);
  std::get<2>(t) = 3;

  std::cout << "x = " << x << std::endl;

  std::vector<std::pair<int &, int &> > v{p, p};
  v[1].second = 4;

  std::cout << "v[0].first = " << v[0].first << std::endl;
}
