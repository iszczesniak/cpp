#include <chrono>
#include <iostream>
#include <queue>

using namespace std;

template <typename Q>
void
time_it(typename Q::value_compare c = {})
{
  using tp_t = chrono::time_point<chrono::high_resolution_clock>;

  tp_t t0 = std::chrono::system_clock::now();

  Q q(c);

  for(int i = 0; i < 1000000; ++i)
    q.push(i);

  while(!q.empty())
    q.pop();

  tp_t t1 = std::chrono::system_clock::now();

  double dt = static_cast<chrono::duration<double>>(t1 - t0).count();

  cout << __PRETTY_FUNCTION__ << " took " << dt << " s" << endl;
}

struct struct_callable
{
  bool
  operator()(const int &a, const int &b) const
  {
    return a < b;
  }
};

using callable = bool(*)(const int &, const int &);

bool
cmp(const int &a, const int &b)
{
  return a < b;
}

int
main()
{
  time_it<priority_queue<int>>();
  time_it<priority_queue<int, vector<int>, struct_callable>>();
  time_it<priority_queue<int, vector<int>, callable>>(cmp);
}
