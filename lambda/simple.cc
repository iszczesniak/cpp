#include <iostream>

using namespace std;

int
main()
{
  auto closure = [](int p){cout << p << endl;};
  closure(1);
}
