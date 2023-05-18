#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <tuple>

struct student
{
  int m_index;
  int m_year;
  std::string m_name;

  bool operator<(const student &b) const
  {
    return std::tie(m_year, m_name) < std::tie(b.m_year, b.m_name);
  }
};

#endif // STUDENT_HPP
