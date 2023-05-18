#include <chrono>
#include <iostream>
#include <functional>
#include <string>
#include <tuple>

using namespace std;

template <typename F, typename T, typename E>
auto
time_it(F &&f, T &&t, E && e)
{
  cout << e << ": ";

  auto t0 = std::chrono::system_clock::now();

  std::apply(std::forward<F>(f), std::forward<T>(t));

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
  A a("a");

  cout << "Results:\n";
  cout << time_it(foo, make_tuple(), "Hello") << " ns\n";
  cout << time_it(goo<int>, make_tuple(1), 3.14159) << " ns\n";
  cout << time_it(&A::foo, forward_as_tuple(a, 1), .1) << " ns\n";
  cout << time_it(&A::goo, forward_as_tuple(A("t"), 1), 1) << " ns\n";
}
