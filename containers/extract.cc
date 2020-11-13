#include <list>
#include <iostream>
#include <set>
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
  set<A> a, b;
  // The temporary object is moved into a container element.
  a.insert(A("A1"));
  a.insert(A("A2"));
  cout << "TEST\n";
  b.insert(a.extract(a.begin()));

  list<A> l;
  {
    // That node handle owns A2.
    auto nh = a.extract(a.begin());
    l.push_back(std::move(nh.value()));
  }

  return 0;
}
