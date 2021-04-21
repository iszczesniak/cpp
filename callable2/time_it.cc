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
  std::chrono::duration<double> dt = t1 - t0;

  return dt;
}

template <typename T>
T
foo(T x)
{
  x += 1;
  return x;
}

struct A
{
  string m_name;

  A(string name): m_name(std::move(name))
  {
  }

  void foo(int x)
  {
    cout << __PRETTY_FUNCTION__ << ": " << m_name << endl;
  }

  void goo(int x)
  {
    cout << __PRETTY_FUNCTION__ << ": " << m_name << endl;
  }
};

int
main()
{
  A a("a"), b("b");

  void (A::* p1)(int) = &A::foo;
  auto p2 = &A::goo;

  (a.*p1)(1);
  (b.*p1)(1);

  (a.*p2)(1);
  (b.*p2)(1);

  time_it(foo<int>, 1);
  time_it(p1, a, 1);
}
