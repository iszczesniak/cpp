#include "timer.hpp"

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

using namespace std;
using namespace std::placeholders;

const auto N = 10000000;

random_device dev;
mt19937 gen(dev());
std::uniform_int_distribution<int> distr;

template <typename C>
void
time_pq(C c)
{
  timer t(__PRETTY_FUNCTION__);

  priority_queue<int, vector<int>, C> q(c);

  for(auto i = N; --i;)
    q.push(distr(gen));

  while(!q.empty())
    q.pop();
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
  time_pq(std::bind(&A::cmp, A(), _1, _2));

  time_pq(function<callable>(functor));
  time_pq(function<callable>(cmp));
  time_pq(function<callable>(closure));
  time_pq(function<callable>(std::bind(&A::cmp, A(), _1, _2)));
}
