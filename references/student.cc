#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>

using namespace std;

struct student
{
  unsigned m_age;
  string m_firstname;
  string m_surname;

  student(unsigned age, string firstname, string surname):
    m_age(age), m_firstname(move(firstname)), m_surname(move(surname))
  {
  }

  bool
  operator <(const student &a) const
  {
    return tie(m_age, m_firstname, m_surname) <
      tie(a.m_age, a.m_firstname, a.m_surname);
  }
};

ostream &
operator << (ostream &out, const student &a)
{
  out << "("
      << a.m_age << ", "
      << a.m_firstname << ", "
      << a.m_surname
      << ")";
  return out;
}

int
main()
{
  set<student> s;
  s.emplace(20, "Betty", "O'Barley");
  s.emplace(19, "Harry", "O'Hay");
  s.emplace(19, "Harry", "Potter");
  for(const auto &e: s)
    cout << e << endl;
}
