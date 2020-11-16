#include <iostream>
#include <forward_list>
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
  // This becomes the first element in the vector.
  cout << "Checkpoint 1\n";
  v.emplace_back("V1");
  cout << "Checkpoint 2\n";
  v.emplace(v.begin(), "V2");
  cout << "Checkpoint 3\n";
  v.emplace(v.end(), "V3");

  for(const auto &e: v)
    cout << e.m_id << endl;
  
  cout << "-------------------------------------------------\n";

  // list<A> l;
  // l.emplace_front("L1");
  // l.emplace_back("L2");

  // cout << "-------------------------------------------------\n";

  // forward_list<A> f;
  // f.emplace_front("L1");
  // f.emplace_after(f.begin(), "L2");

  // // We can't emplace at the back, because we don't have an iterator
  // // to the preceeding element in the list.

  // // f.emplace_back("L3");

  // cout << "-------------------------------------------------\n";

  // set<A> s;
  // s.emplace("S1");

  // cout << "-------------------------------------------------\n";

  return 0;
}
