#include <chrono>
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

template <typename C>
void
time_it(C c)
{
  using tp_t = chrono::time_point<chrono::high_resolution_clock>;

  tp_t t0 = std::chrono::system_clock::now();

  priority_queue<int, vector<int>, C> q(c);

  for(int i = 0; i < 10000000; ++i)
    q.push(i);

  while(!q.empty())
    q.pop();

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

  time_it(functor);
  time_it(cmp);
  time_it(closure);

  time_it(function<callable>(functor));
  time_it(function<callable>(cmp));
  time_it(function<callable>(closure));
}
