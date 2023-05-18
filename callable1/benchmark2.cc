#include "student.hpp"
#include "test_pq.hpp"
#include "timer.hpp"

#include <iostream>
#include <tuple>

using namespace std;

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
  cout << "Compare with a closure -----------------------------\n";
  doit(priority_queue<student, vector<student>,
       bool(*)(const student &, const student &)>
       ([](const student &a, const student &b)
       {
	 return tie(a.m_year, a.m_name) < tie(b.m_year, b.m_name);
       }));
}
