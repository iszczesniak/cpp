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

  auto r = std::invoke(f, std::forward<Args>(args)...);

  auto t1 = std::chrono::system_clock::now();
  std::chrono::duration<double> dt = t1 - t0;

  return std::make_pair(r, dt);
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

  void foo()
  {
    cout << __PRETTY_FUNCTION__ << ": " << m_name << endl;
  }

  void goo()
  {
    cout << __PRETTY_FUNCTION__ << ": " << m_name << endl;
  }
};

int
main()
{
  A a("a"), b("b");

  void (A::* p1)() = &A::foo;
  auto p2 = &A::goo;

  (a.*p1)();
  (b.*p1)();

  (a.*p2)();
  (b.*p2)();

  time_it(foo<int>, 1);
}
