#include "timer.hpp"

#include <iostream>
#include <functional>
#include <string>

using namespace std;

// Exercise: how does the volatile qualifier below affect the results?
volatile long long int x;

constexpr auto N = 1000000000;

template <typename F, typename ... Args>
void
time_regular(F &&f, Args &&... args)
{
  timer t(__PRETTY_FUNCTION__);

  for(auto i = N; i--;)
    std::forward<F>(f)(std::forward<Args>(args)...);
}

template <typename F, typename O, typename ... Args>
void
time_member(F &&f, O &&o, Args &&... args)
{
  timer t(__PRETTY_FUNCTION__);

  for(auto i = N; i--;)
    (std::forward<O>(o).*std::forward<F>(f))(std::forward<Args>(args)...);
}

template <typename F, typename ... Args>
void
time_invoke(F &&f, Args &&... args)
{
  timer t(__PRETTY_FUNCTION__);

  for(auto i = N; i--;)
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
}

template <typename F, typename Args>
void
time_apply(F &&f, Args args)
{
  timer t(__PRETTY_FUNCTION__);

  for(auto i = N; i--;)
    std::apply(std::forward<F>(f), std::forward<Args>(args));
}

void
foo()
{
  x += 1;
}

void
foo2(int i)
{
  x += i;
}

template <typename T>
void
goo()
{
  x += 1;
}

template <typename T>
void
goo2(int i)
{
  x += i;
}

struct A
{
  void foo()
  {
    x += 1;
  }

  void foo2(int i)
  {
    x += i;
  }

  void operator()()
  {
    x += 1;
  }

  void operator()(int i)
  {
    x += i;
  }
};

int
main()
{
  A a;

  // Exercise: pass the callables wrapped in std::function.
  time_regular(foo);
  time_regular(foo2, 1);
  time_regular(goo<int>);
  time_regular(goo2<int>, 1);
  time_regular(a);
  time_regular(a, 1);
  time_regular([]{x += 1;});
  time_regular([](int){x += 1;}, 1);
  time_member(&A::foo, a);
  time_member(&A::foo2, a, 1);

  time_invoke(foo);
  time_invoke(foo2, 1);
  time_invoke(goo<int>);
  time_invoke(goo2<int>, 1);
  time_invoke(a);
  time_invoke(a, 1);
  time_invoke([]{x += 1;});
  time_invoke([](int){x += 1;}, 1);
  time_invoke(&A::foo, a);
  time_invoke(&A::foo2, a, 1);

  time_apply(foo, make_tuple());
  time_apply(foo2, make_tuple(1));
  time_apply(goo<int>, make_tuple());
  time_apply(goo2<int>, make_tuple(1));
  time_apply(a, make_tuple());
  time_apply(a, make_tuple(1));
  time_apply([]{x += 1;}, make_tuple());
  time_apply([](int){x += 1;}, make_tuple(1));
  time_apply(&A::foo, forward_as_tuple(a));
  time_apply(&A::foo2, forward_as_tuple(a, 1));

  cout << "Called " << x << " callables.\n";
}
