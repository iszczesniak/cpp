#include <chrono>
#include <iostream>
#include <functional>
#include <string>

using namespace std;

template <typename F, typename ... Args>
auto
time_it(F f, Args &&... args)
{
  auto t0 = std::chrono::system_clock::now();

  std::invoke(f, std::forward<Args>(args)...);

  auto t1 = std::chrono::system_clock::now();
  std::chrono::nanoseconds dt = t1 - t0;

  return dt.count();
}

template <typename T>
void
foo(T x)
{
  cout << __PRETTY_FUNCTION__ << " took ";
}

struct A
{
  string m_name;

  A(string name): m_name(std::move(name))
  {
  }

  void foo(int x)
  {
    cout << __PRETTY_FUNCTION__ << " for " << m_name << " took ";
  }

  void goo(int x)
  {
    cout << __PRETTY_FUNCTION__ << " for " << m_name << " took ";
  }
};

int
main()
{
  A a("a"), b("b");

  void (A::* p1)(int) = &A::foo;
  auto p2 = &A::goo;

  //  (a.*p1)(1);
  //  (b.*p1)(1);

  //  (a.*p2)(1);
  //  (b.*p2)(1);

  cout << time_it(foo<int>, 1) << " ns\n";
  cout << time_it(p1, a, 1) << " ns\n";
  cout << time_it(foo<int>, 1) << " ns\n";
  cout << time_it(p1, a, 1) << " ns\n";
}
