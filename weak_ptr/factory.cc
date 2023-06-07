#include "factory.hpp"

#include <cassert>
#include <iostream>
#include <map>
#include <memory>

using namespace std;

struct A
{
  static int counter;

  int m_id;
  int m_unique;

  A(int id): m_id(id), m_unique(counter++)
  {
    cout << "ctor: " << m_id << ", " << m_unique << '\n';
  }

  ~A()
  {
    cout << "dtor: " << m_id << ", " << m_unique << '\n';
  }
};

int A::counter = 0;

int
main()
{
  int unique;

  {
    auto sp1 = factory<A>(1);
    auto sp2 = factory<A>(1);
    unique = sp1->m_unique;
    assert(sp1->m_unique == sp2->m_unique);
  }

  auto sp1 = factory<A>(1);
  assert(unique != sp1->m_unique);
}
