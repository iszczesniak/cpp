#include <cassert>
#include <iostream>

struct student
{
  int m_year;
  std::string m_name;
};

int main()
{
  auto c = [flag = true](const student &a, const student &b)
  {
    return flag ? a.m_name < b.m_name : a.m_year < b.m_year;
  };

  student boe{2, "Boe"}, joe{1, "Joe"};

  struct
  {
    bool flag = true;
    bool operator() (const student &a, const student &b) const
    {
      return flag ? a.m_name < b.m_name : a.m_year < b.m_year;
    }
  } f;

  assert(c(boe, joe));
  assert(f(boe, joe));
}
