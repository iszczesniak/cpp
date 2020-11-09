#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct A
{
  string m_text;

  A(const string &text): m_text(text)
  {
    cout << "ctor: " << m_text << endl;
  }

  A(const A &a): m_text(a.m_text)
  {
    cout << "copy ctor: " << m_text << endl;
  }

  A(A &&a): m_text(move(a.m_text))
  {
    cout << "move ctor: " << m_text << endl;
  }
  
  ~A()
  {
    cout << "dtor: " << m_text << endl;
  }

  A &operator = (const A &a)
  {
    m_text = a.m_text;
    cout << "copy-assignment: " << m_text << endl;    
  }

  A &operator = (A &&a)
  {
    m_text = move(a.m_text);
    cout << "move-assignment: " << m_text << endl;    
  }
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

  while(!q.empty())
    {
      cout << q.top().m_text << endl;
      q.pop();
    }
  
  return 0;
}
