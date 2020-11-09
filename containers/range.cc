#include <iostream>
#include "range.hpp"

using namespace std;

int main()
{
  for(auto i: range<int>(1, 11))
    cout << i << endl;
}
