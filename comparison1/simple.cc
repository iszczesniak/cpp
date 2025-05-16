#include <cassert>

struct A
{
  int m_id;
};

int operator <=> (const A &i, const A &j)
{
  if (i.m_id < j.m_id)
    return -1;
  if (i.m_id > j.m_id)
    return 1;

  return 0;
}

int main()
{
  A i{10}, j{20};

  assert((i <=> j) == -1);
}
