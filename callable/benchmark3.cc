#include "student.hpp"
#include "test_pq.hpp"
#include "timer.hpp"

#include <iostream>
#include <tuple>

using namespace std;

struct fun
{
  bool m_flag;

  fun(bool flag): m_flag(flag)
  {
  }

  bool operator()(const student &a, const student &b) const
  {
    return m_flag ? tie(a.m_year, a.m_name) < tie(b.m_year, b.m_name)
		  : tie(a.m_year, a.m_name) > tie(b.m_year, b.m_name);
  }
};

int
main()
{
  bool flag = true;
  cout << "Compare with a functor -----------------------------\n";
  doit(priority_queue<student, vector<student>, fun>(fun(flag)));
  cout << "Compare with a closure -----------------------------\n";

  auto c = [flag](const student &a, const student &b)
  {
    return flag ? tie(a.m_year, a.m_name) < tie(b.m_year, b.m_name)
		: tie(a.m_year, a.m_name) > tie(b.m_year, b.m_name);
  };
  doit(priority_queue<student, vector<student>, decltype(c)>(c));
}
