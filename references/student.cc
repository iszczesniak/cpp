#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>

using namespace std;

struct student
{
  unsigned m_age;
  string m_fn;
  string m_ln;

  student(unsigned age, string fn, string ln):
    m_age(age), m_fn(move(fn)), m_ln(move(ln))
  {
  }

  bool
  operator <(const student &a) const
  {
    // Function std::tie returns a tuple of const references.  We use
    // the < operator defined for a tuple, which compares
    // lexicographically.  There is no overhead of std::tie, because
    // it's optimized out.
    return tie(m_age, m_fn, m_ln) < tie(a.m_age, a.m_fn, a.m_ln);
  }
};

ostream &
operator << (ostream &out, const student &a)
{
  out << "(" << a.m_age << ", " << a.m_fn << ", " << a.m_ln << ")";
  return out;
}

int
main()
{
  set<student> s;
  s.emplace(19, "Betty", "O'Barley");
  s.emplace(20, "Harry", "O'Hay");
  s.emplace(20, "Harry", "Potter");
  for(const auto &e: s)
    cout << e << endl;
}
