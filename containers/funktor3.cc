#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct A
{
  A(const string &text): m_text(text) {}
  string m_text;
};

struct CMP
{
  bool m_order;
  CMP(bool order): m_order(order) {}
  bool operator () (const A &e1, const A &e2)
  {
    bool s = e1.m_text < e2.m_text;
    return m_order ? !s : s;
  }
};

int
main(void)
{
  priority_queue<A, vector<A>, CMP> q(CMP(true));

  q.push(A("a2"));
  q.push(A("a0"));
  q.push(A("a1"));

  while(!q.empty())
    {
      cout << q.top().m_text << endl;
      q.pop();
    }
  
  return 0;
}
