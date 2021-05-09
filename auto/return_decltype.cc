#include <tuple>

int &f1()
{
  static int i = 1;
  return i;
}

int f2()
{
  return 1;
}

template <typename F>
decltype(auto) foo(F &&f)
{
  return std::forward<F>(f)();
}

int main()
{
  auto &&r1 = foo(f1);
  auto &&r2 = foo(f2);
}
