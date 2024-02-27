#include <algorithm>
#include <chrono>
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
    auto t0 = std::chrono::system_clock::now();

    for(int i = 0; i < n; ++i)
      v.push_back(distr(gen));

    auto t1 = std::chrono::system_clock::now();
    double dt = static_cast<chrono::duration<double>>(t1 - t0).count();

    cout << "generation: " << dt << " s\n";
  }

  {
    auto t0 = std::chrono::system_clock::now();

    sort(v.begin(), v.end());

    auto t1 = std::chrono::system_clock::now();
    double dt = static_cast<chrono::duration<double>>(t1 - t0).count();

    cout << "sorting: " << dt << " s\n";
  }
}
