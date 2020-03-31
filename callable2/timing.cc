#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 100000000;

template <typename C>
void
time_pq(C c)
{
  using tp_t = chrono::time_point<chrono::high_resolution_clock>;

  tp_t t0 = std::chrono::system_clock::now();

  priority_queue<int, vector<int>, C> q(c);

  for(int i = 0; i < N; ++i)
    q.push(i);

  while(!q.empty())
    q.pop();

  tp_t t1 = std::chrono::system_clock::now();

  double dt = static_cast<chrono::duration<double>>(t1 - t0).count();

  cout << __PRETTY_FUNCTION__ << " took " << dt << " s" << endl;
}

template <typename C>
void
time_sort(C c)
{
  using tp_t = chrono::time_point<chrono::high_resolution_clock>;

  vector<int> v(N);

  for(int i = 0; i < v.size(); ++i)
    v[i] = -i;

  tp_t t0 = std::chrono::system_clock::now();

  sort(v.begin(), v.end(), c);

  tp_t t1 = std::chrono::system_clock::now();

  double dt = static_cast<chrono::duration<double>>(t1 - t0).count();

  cout << __PRETTY_FUNCTION__ << " took " << dt << " s" << endl;
}

bool
cmp(const int &a, const int &b)
{
  return a < b;
}

using callable = bool(const int &, const int &);

int
main()
{
  auto functor = less<int>{};
  auto closure = [](const int &a, const int &b){return a < b;};

  time_pq(functor);
  time_pq(cmp);
  time_pq(closure);
  time_pq(function<callable>(functor));
  time_pq(function<callable>(cmp));
  time_pq(function<callable>(closure));

  time_sort(functor);
  time_sort(cmp);
  time_sort(closure);
  time_sort(function<callable>(functor));
  time_sort(function<callable>(cmp));
  time_sort(function<callable>(closure));
}
