#include <iostream>
#include <set>

using namespace std;

struct A
{
  int m_id;

  A(int id): m_id(id)
  {
    cout << "ctor\n";
  }

  ~A()
  {
    cout << "dtor\n";
  }

  A(const A &a) = delete;
  A& operator = (const A &a) = delete;

  A(A &&a): m_id(a.m_id)
  {
    cout << "move-ctor\n";
  }

  A &
  operator = (A &&a)
  {
    m_id = a.m_id;
    cout << "move-assignment\n";
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
  // The temporary object is moved into a container.
  a.insert(A(1));
  cout << "TEST\n";
  //  b.insert(a.extract(a.begin()));
  return 0;
}
