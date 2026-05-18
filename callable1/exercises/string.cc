#include <cassert>
#include <string>

using namespace std;

struct cmp
{
  bool m_flag;

  cmp(bool flag): m_flag(flag)
  {
  }
  
  bool operator()(const string &a, const string &b)
  {
    return m_flag ? a > b : a < b;
  }
};

int main()
{
  bool flag = false;

  cmp f(flag);

  auto c = [flag](const string &a, const string &b)
  {
    return flag ? a > b : a < b;
  };

  string b = "p", d = "q";
  
  assert(flag ^ f(b, d));
  assert(flag ^ c(b, d));
}
