#include "pimpl1.hpp"
#include "pimpl2.hpp"

#include <iostream>

using namespace std;

struct A
{
  int m_id;

  A(int id): m_id(id)
  {
    cout << "ctor: " << m_id << '\n';
  }

  ~A()
  {
    cout << "dtor: " << m_id << '\n';
  }
};

auto foo1(bool flag)
{
  // C++17: deducing the template argument of pimpl1.
  pimpl1 a(new A(1));
  pimpl1 b(new A(2));

  return flag ? a : b;
}

auto foo2(bool flag)
{
  pimpl2 a(new A(1));
  pimpl2 b(new A(2));

  return flag ? move(a) : move(b);
}

int
main()
{
  volatile bool flag = false;

  {
    auto a = foo1(flag);
    auto b = a;
  }

  cout << "---\n";
  
  {
    auto a = foo2(flag);
    auto b = move(a);
  }
}
