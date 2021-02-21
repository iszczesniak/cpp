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
};

int main()
{
  cout << "vector: -----------------------------------------\n";

  {
    vector<A> v;

    // Uncommend the line below to prevent vector reallocation.
    // v.reserve(3);

    auto i1 = v.begin();

    // This becomes the first element in the vector.
    cout << "Checkpoint V1\n";
    v.emplace_back("V1");
    cout << "Checkpoint V2\n";
    v.emplace(v.begin(), "V2");
    cout << "Checkpoint V3\n";
    v.emplace(v.end(), "V3");

    cout << "The vector elements are:\n";
    for(const auto &e: v)
      cout << e.m_id << endl;

    cout << "The vector was relocated: " << boolalpha
         << (i1 != v.begin()) << endl;
  }
  
  cout << "list: -------------------------------------------\n";

  {
    list<A> l;
    // We can emplace at the front, and at the back, because the list
    // is doubly-linked.
    l.emplace_front("L1");
    l.emplace_back("L2");
    l.emplace(++(l.begin()), "L3");

    cout << "The list elements are:\n";
    for(const auto &e: l)
      cout << e.m_id << endl;
  }
  
  cout << "forward_list: -----------------------------------\n";

  {
    forward_list<A> f;
    f.emplace_front("L1");
    // We can emplace after an element, but not before, because it's a
    // singly-linked list.
    f.emplace_after(f.begin(), "L2");

    // We can't emplace at the back, because we don't have an iterator
    // to the preceeding element in the list.

    // f.emplace_back("L3");

    cout << "The forward_list elements are:\n";
    for(const auto &e: f)
      cout << e.m_id << endl;

  }

  return 0;
}
