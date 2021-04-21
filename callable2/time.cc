#include <chrono>
#include <functional>

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
  void foo()
  {
    std::cout << __PRETTY_FUNCTION__ << ": ";

  }

  void goo()
  {
    std::cout << __PRETTY_FUNCTION__ << ": ";

  }
};

int
main()
{
  time_it(foo<int>, 1);
}
