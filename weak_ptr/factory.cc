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

auto
factory(int id)
{
  shared_ptr<A> sp;

  static map<int, weak_ptr<A>> cache;
  auto i = cache.find(id);

  if (i != cache.end())
    sp = i->second.lock();

  if (sp == nullptr)
    {
      sp = make_shared<A>(id);
      cache.insert(i, make_pair(id, sp));
    }

  return sp;
}

int
main()
{
  int unique;

  {
    auto sp1 = factory(1);
    auto sp2 = factory(1);
    unique = sp1->m_unique;
    assert(sp1->m_unique == sp2->m_unique);
  }

  auto sp1 = factory(1);
  assert(unique != sp1->m_unique);
}
