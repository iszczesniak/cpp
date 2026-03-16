#include <iostream>
#include <tuple>

using namespace std;

int main()
{
  int x = 1, y = 2;

  std::tuple<int &> tx{x}, ty{y};
  tx = ty;

  cout << "x = " << x << endl;
  cout << "y = " << y << endl;

  std::get<0>(tx) = 0;

  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
}
