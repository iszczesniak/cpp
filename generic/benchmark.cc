#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

using tp_t = chrono::time_point<chrono::high_resolution_clock>;

int main()
{
  random_device dev;
  mt19937 gen(dev());
  std::uniform_int_distribution<int> distr;

  vector<int> v;
  v.reserve(100000000);

  {
    tp_t t0 = std::chrono::system_clock::now();

    while(v.size() < v.capacity())
      v.push_back(distr(gen));

    tp_t t1 = std::chrono::system_clock::now();
    double dt = static_cast<chrono::duration<double>>(t1 - t0).count();

    cout << "generation: " << dt << " s\n";
  }

  {
    using tp_t = chrono::time_point<chrono::high_resolution_clock>;
    tp_t t0 = std::chrono::system_clock::now();

    sort(v.begin(), v.end());

    tp_t t1 = std::chrono::system_clock::now();
    double dt = static_cast<chrono::duration<double>>(t1 - t0).count();

    cout << "sorting: " << dt << " s\n";
  }
}
