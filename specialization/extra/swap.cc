#include <algorithm>
#include <iostream>
#include <vector>

struct A
{
  int m_i;

  int m_count = 0;

  A(int i): m_i(i)
  {
  }

  bool
  operator<(const A &a) const
  {
    return m_i < a.m_i;
  }
};

std::ostream &
operator << (std::ostream &os, const A &a)
{
  os << "(" << a.m_i << ", " << a.m_count << ")";
  return os;
}

template <>
void
constexpr std::swap(A &a, A &b) noexcept
{
  int i = b.m_i;
  b.m_i = a.m_i;
  a.m_i = i;
  ++a.m_count;
  ++b.m_count;
}

int
main()
{
  std::vector v = {A(3), A(1), A(2)};
  for(const auto &e: v)
    std::cout << e << std::endl;
  std::sort(v.begin(), v.end());
  for(const auto &e: v)
    std::cout << e << std::endl;
}
