#include <string>
#include <utility>

struct A {};

struct B: A
{
  std::string m_s;

  B & operator=(B &&b)
  {
    A::operator=(std::move(b));
    m_s = std::move(b.m_s);
    return *this;
  }
};
