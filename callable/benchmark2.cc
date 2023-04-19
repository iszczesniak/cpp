#include "timer.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

struct student
{
  int m_index;
  int m_year;
  string m_name;

  bool operator<(const student &b) const
  {
    return tie(m_year, m_name) < tie(b.m_year, b.m_name);
  }
};

bool foo(const student &a, const student &b)
{
  return tie(a.m_year, a.m_name) < tie(b.m_year, b.m_name);
}

struct fun
{
  bool operator()(const student &a, const student &b) const
  {
    return tie(a.m_year, a.m_name) < tie(b.m_year, b.m_name);
  }
};

template <typename Q>
void
doit(Q &&q)
{
  timer t("together");

  {
    random_device dev;
    mt19937 gen(dev());
    std::uniform_int_distribution<int> distr;

    timer t("pushing");
    string name = "abcdefghijklmnop";

    for(int i = 0; i < 10000000; ++i)
      {
	int index = distr(gen);
	int year = index % 5 + 1;

	q.push(student(index, year, name));

	next_permutation(name.begin(), name.end());
      }
  }

  {
    timer t("popping");
    while(!q.empty())
      q.pop();
  }
}

int
main()
{
  cout << "Compare with the member operator < -----------------\n";
  doit(priority_queue<student>());
  cout << "Compare with non-member function -------------------\n";
  doit(priority_queue<student, vector<student>,
       bool(*)(const student &, const student &)>(foo));
  cout << "Compare with a functor -----------------------------\n";
  doit(priority_queue<student, vector<student>, fun>(fun()));
}
