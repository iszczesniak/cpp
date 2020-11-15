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
  operator = (A &&a) noexcept
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
  // Moves the element into a container.
  v.push_back(A("V1"));
  cout << "Before insert.\n";
  v.insert(v.begin(), A("V2"));
  cout << "after insert.\n";

  // list<A> l;

  // set<A> s;

  return 0;
}
