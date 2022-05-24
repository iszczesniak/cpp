#include <chrono>
#include <iostream>
#include <functional>
#include <string>

using namespace std;

volatile int x;

constexpr int N = 1000000000;

template <typename F, typename ... Args>
void
time_normal1(F &&f, Args &&... args)
{
  cout << __PRETTY_FUNCTION__ << ": ";

  auto t0 = std::chrono::system_clock::now();

  for(int i = 0; i < N; ++i)
    std::forward<F>(f)(std::forward<Args>(args)...);

  auto t1 = std::chrono::system_clock::now();
  std::chrono::nanoseconds dt = t1 - t0;

  cout << dt.count() / N << " ns\n";;
}

template <typename F, typename O, typename ... Args>
void
time_normal2(F &&f, O &&o, Args &&... args)
{
  cout << __PRETTY_FUNCTION__ << ": ";

  auto t0 = std::chrono::system_clock::now();

  for(int i = 0; i < N; ++i)
    (o.*std::forward<F>(f))(std::forward<Args>(args)...);

  auto t1 = std::chrono::system_clock::now();
  std::chrono::nanoseconds dt = t1 - t0;

  cout << dt.count() / N << " ns\n";;
}

template <typename F, typename ... Args>
void
time_invoke(F &&f, Args &&... args)
{
  cout << __PRETTY_FUNCTION__ << ": ";

  auto t0 = std::chrono::system_clock::now();

  for(int i = 0; i < N; ++i)
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

  auto t1 = std::chrono::system_clock::now();
  std::chrono::nanoseconds dt = t1 - t0;

  cout << dt.count() / N << " ns\n";;
}

template <typename F, typename Args>
void
time_apply(F &&f, Args args)
{
  cout << __PRETTY_FUNCTION__ << ": ";

  auto t0 = std::chrono::system_clock::now();

  for(int i = 0; i < N; ++i)
    std::apply(std::forward<F>(f), std::forward<Args>(args));

  auto t1 = std::chrono::system_clock::now();
  std::chrono::nanoseconds dt = t1 - t0;

  cout << dt.count() / N << " ns\n";
}

void
foo()
{
  ++x;
}

void
foo2(int)
{
  ++x;
}

template <typename T>
void
goo()
{
  ++x;
}

template <typename T>
void
goo2(int)
{
  ++x;
}

struct A
{
  void foo()
  {
    ++x;
  }

  void foo2(int)
  {
    ++x;
  }

  void operator()()
  {
    ++x;
  }

  void operator()(int)
  {
    ++x;
  }
};

int
main()
{
  A a;

  time_normal1(foo);
  time_normal1(foo2, 1);
  time_normal1(goo<int>);
  time_normal1(goo2<int>, 1);
  time_normal1(a);
  time_normal1(a, 1);
  time_normal1([]{++x;});
  time_normal1([](int){++x;}, 1);
  time_normal2(&A::foo, a);
  time_normal2(&A::foo2, a, 1);

  time_invoke(foo);
  time_invoke(foo2, 1);
  time_invoke(goo<int>);
  time_invoke(goo2<int>, 1);
  time_invoke(a);
  time_invoke(a, 1);
  time_invoke([]{++x;});
  time_invoke([](int){++x;}, 1);
  time_invoke(&A::foo, a);
  time_invoke(&A::foo2, a, 1);

  time_apply(foo, make_tuple());
  time_apply(foo2, make_tuple(1));
  time_apply(goo<int>, make_tuple());
  time_apply(goo2<int>, make_tuple(1));
  time_apply(a, make_tuple());
  time_apply(a, make_tuple(1));
  time_apply([]{++x;}, make_tuple());
  time_apply([](int){++x;}, make_tuple(1));
  time_apply(&A::foo, forward_as_tuple(a));
  time_apply(&A::foo2, forward_as_tuple(a, 1));
}
