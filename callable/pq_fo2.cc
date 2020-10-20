#include <functional>
#include <iostream>
#include <queue>

using namespace std;

struct CMP
{
  bool m_order;

  CMP(bool order): m_order(order)
  {
  }

  bool
  operator()(const int &a, const int &b) const
  {
    return m_order ? a < b : a > b;
  }
};

int
main(void)
{
  priority_queue<int, vector<int>, CMP> q(CMP(false));

  q.push(2);
  q.push(1);
  q.push(3);

  while(!q.empty())
    {
      cout << q.top() << endl;
      q.pop();
    }
  
  return 0;
}
