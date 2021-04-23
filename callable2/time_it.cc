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

void
foo()
{
  cout << __PRETTY_FUNCTION__ << " took ";
}

template <typename T>
void
goo(T x)
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

  cout << "Results:\n";
  cout << time_it(goo) << " ns\n";
  cout << time_it(foo<int>, 1) << " ns\n";
  cout << time_it(&A::foo, a, 1) << " ns\n";
  cout << time_it(&A::goo, b, 1) << " ns\n";
}
