#include "timer.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main()
{
  const auto N = 100000000;

  random_device dev;
  mt19937 gen(dev());
  std::uniform_int_distribution<int> distr;

  vector<pair<int, int>> v;
  v.reserve(N);

  timer t("together");
  {
    timer t("generation");

    for(auto i = N; --i;)
      v.push_back(make_pair(distr(gen), i >> 4));
  }

  {
    timer t("sorting");

    // By default, sort uses std::less to compare elements, which in
    // turn uses operator < for std::less that compares
    // lexicographically.
    sort(v.begin(), v.end());
  }
}
