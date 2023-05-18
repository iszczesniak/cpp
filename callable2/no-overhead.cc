#include "timer.hpp"

#include <chrono>
#include <iostream>
#include <functional>
#include <string>

using namespace std;

typedef std::chrono::duration<long long, pico> picoseconds;

long long int x;

constexpr auto N = 10000000;

template <typename F, typename ... Args>
void
time_regular(F &&f, Args &&... args)
{
  timer t(__PRETTY_FUNCTION__);

  for(auto i = N; --i;)
    std::forward<F>(f)(std::forward<Args>(args)...);
}

template <typename F, typename O, typename ... Args>
void
time_member(F &&f, O &&o, Args &&... args)
{
  timer t(__PRETTY_FUNCTION__);

  for(auto i = N; --i;)
    (std::forward<O>(o).*std::forward<F>(f))(std::forward<Args>(args)...);
}

template <typename F, typename ... Args>
void
time_invoke(F &&f, Args &&... args)
{
  timer t(__PRETTY_FUNCTION__);

  for(auto i = N; --i;)
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
}

template <typename F, typename Args>
void
time_apply(F &&f, Args args)
{
  timer t(__PRETTY_FUNCTION__);

  for(auto i = N; --i;)
    std::apply(std::forward<F>(f), std::forward<Args>(args));
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

  time_regular(foo);
  time_regular(foo2, 1);
  time_regular(goo<int>);
  time_regular(goo2<int>, 1);
  time_regular(a);
  time_regular(a, 1);
  time_regular([]{++x;});
  time_regular([](int){++x;}, 1);
  time_member(&A::foo, a);
  time_member(&A::foo2, a, 1);

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

  cout << "Called " << x << " callables.\n";
}
