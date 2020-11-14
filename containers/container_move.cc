#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <string>

using namespace std;

struct A
{
  string m_id;

  A(string &&id): m_id(std::move(id))
  {
    cout << "ctor: " << m_id << '\n';
  }

  ~A()
  {
    cout << "dtor: " << m_id << '\n';
  }

  A(const A &a): m_id(a.m_id)
  {
    cout << "copy-ctor: " << m_id << '\n';
  }

  A& operator = (const A &a) = delete;

  A(A &&a): m_id(std::move(a.m_id))
  {
    cout << "move-ctor: " << m_id << '\n';
  }

  A &
  operator = (A &&a)
  {
    m_id = std::move(a.m_id);
    cout << "move-assignment: " << m_id << '\n';
    return *this;
  }

  bool
  operator < (const A &a) const
  {
    return m_id < a.m_id;
  }
};

int main()
{
  vector<A> va{A("A1")}, vb;
  cout << "Moving a container touches no element.\n";
  va = move(vb);
  
  list<A> la{A("A1")}, lb;
  cout << "Moving a container touches no element.\n";
  la = move(lb);

  set<A> sa{A("A1")}, sb;
  cout << "Moving a container touches no element.\n";
  sa = move(sb);

  return 0;
}
