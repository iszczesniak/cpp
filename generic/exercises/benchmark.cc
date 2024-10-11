#include "timer.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main()
{
  const int n = 100000000;

  random_device dev;
  mt19937 gen(dev());
  std::uniform_int_distribution<int> distr;

  vector<int> v;
  v.reserve(n);

  {
    timer t("generation");

    for(int i = 0; i < n; ++i)
      v.push_back(distr(gen));
  }

  {
    timer t("sorting");

    sort(v.begin(), v.end());
  }
}
