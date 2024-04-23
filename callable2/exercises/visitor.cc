#include <functional>
#include <iostream>

using namespace std;

struct A
{
  void lfoo(int &)
  {
    cout << __PRETTY_FUNCTION__ << endl;
  }

  void rfoo(int &&)
  {
    cout << __PRETTY_FUNCTION__ << endl;
  }
};

template <typename F, typename A>
struct visitor
{
  F m_f;
  A &m_a;

  visitor(F f, A &a): m_f(f), m_a(a)
  {
  }

  template <typename T>
  decltype(auto) operator()(T &&t)
  {
    return (m_a.*m_f)(forward<T>(t));
    // return std::invoke(m_f, m_a, forward<T>(t));
  }
};

int
main()
{
  A a;
  int x = 1;
  visitor lv(&A::lfoo, a);
  lv(x);
  visitor(&A::lfoo, a)(x);

  visitor rv(&A::rfoo, a);
  rv(1);
  visitor(&A::rfoo, a)(1);

  auto c1 = [&a](auto &&t){a.lfoo(forward<decltype(t)>(t));};
  c1(x);
  auto c2 = [&a](auto &&t){a.rfoo(forward<decltype(t)>(t));};
  c2(1);
}
