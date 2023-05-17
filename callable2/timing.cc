#include "timer.hpp"

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 10000000;

template <typename C>
void
time_pq(C c)
{
  timer t(__PRETTY_FUNCTION__);

  priority_queue<int, vector<int>, C> q(c);

  for(int i = 0; i < N; ++i)
    q.push(i);

  while(!q.empty())
    q.pop();
}

template <typename C>
void
time_sort(C c)
{
  timer t(__PRETTY_FUNCTION__);
  
  vector<int> v(N);

  for(int i = 0; i < v.size(); ++i)
    v[i] = i;

  sort(v.begin(), v.end(), c);
}

bool
cmp(const int &a, const int &b)
{
  return a < b;
}

struct A
{
  bool
  cmp(const int &a, const int &b)
  {
    return a < b;
  }
};

using callable = bool(const int &, const int &);

int
main()
{
  auto functor = less<int>{};
  auto closure = [](const int &a, const int &b){return a < b;};

  time_pq(functor);
  time_pq(cmp);
  time_pq(closure);
  time_pq(std::bind(&A::cmp, A(),
                    std::placeholders::_1,
                    std::placeholders::_2));

  time_pq(function<callable>(functor));
  time_pq(function<callable>(cmp));
  time_pq(function<callable>(closure));
  time_pq(function<callable>(std::bind(&A::cmp, A(),
                                       std::placeholders::_1,
                                       std::placeholders::_2)));

  time_sort(functor);
  time_sort(cmp);
  time_sort(closure);
  time_sort(std::bind(&A::cmp, A(),
                      std::placeholders::_1,
                      std::placeholders::_2));

  time_sort(function<callable>(functor));
  time_sort(function<callable>(cmp));
  time_sort(function<callable>(closure));
  time_sort(function<callable>(std::bind(&A::cmp, A(),
                                         std::placeholders::_1,
                                         std::placeholders::_2)));
}
