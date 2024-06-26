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
    m_id += "-copied";
    cout << "copy-ctor: " << m_id << '\n';
  }

  A(A &&a): m_id(std::move(a.m_id))
  {
    m_id += "-moved";
    cout << "copy-ctor: " << m_id << '\n';
  }

  A& operator = (const A &a) = delete;
  A& operator = (A &&a) = delete;

  bool
  operator < (const A &a) const
  {
    return m_id < a.m_id;
  }
};

int main()
{
  // A temporary object is not moved but copied because {A("V1")}
  // creates an std::initializer_list object that provides access to
  // its elements through a const reference.
  vector<A> va, vb{A("V1")};
  cout << "Moving a container touches no element.\n";
  va = std::move(vb);

  cout << "-------------------------------------------------\n";
  
  // A temporary object is not moved but copied.  I don't know why.
  list<A> la, lb{A("L1")};
  cout << "Moving a container touches no element.\n";
  la = std::move(lb);

  cout << "-------------------------------------------------\n";

  // A temporary object is not moved but copied.  I don't know why.
  set<A> sa, sb{A("S1")};
  cout << "Moving a container touches no element.\n";
  sa = std::move(sb);

  cout << "-------------------------------------------------\n";

  return 0;
}
