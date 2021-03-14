#include <algorithm>
#include <iostream>
#include <vector>

struct A
{
  int m_i;
  A(int i): m_i()
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
  os << a.m_i;
  return os;
}

void
swap(A &a, A &b) noexcept
{
  std::cout << "Swapping " << a << " with " << b << std::endl;
}

int
main()
{
  std::vector v = {A(3), A(1), A(2)};
  std::sort(v.begin(), v.end());
}
