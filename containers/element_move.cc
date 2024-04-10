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

  A(const A &a) = delete;
  A& operator = (const A &a) = delete;

  A(A &&a): m_id(std::move(a.m_id))
  {
    m_id += "-moved";
    cout << "move-ctor: " << m_id << '\n';
  }

  A &
  operator = (A &&a)
  {
    m_id = std::move(a.m_id) + "-moved";
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
  vector<A> v;
  cout << "Vector push_back:\n";
  v.push_back(A("V1"));
  cout << "Vector insert:\n";
  v.insert(v.begin(), A("V2"));
  cout << "Vector element assignment:\n";
  A a = std::move(v[0]);

  cout << "-------------------------------------------------\n";

  list<A> l;
  cout << "List push_back:\n";
  l.push_back(A("L1"));
  cout << "List push_front:\n";
  l.push_front(A("L2"));
  cout << "List element assignment:\n";
  (*l.begin()) = std::move(a);

  cout << "-------------------------------------------------\n";

  set<A> s;
  cout << "Set insert:\n";
  s.insert(A("S2"));
  cout << "Set insert again:\n";
  s.insert(A("S1"));

  cout << "-------------------------------------------------\n";

  return 0;
}
