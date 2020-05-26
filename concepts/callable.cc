#include <string>

using namespace std;

template <typename F, typename ... Args>
concept bool Callable = requires(F f, Args ... args)
{
  f(args...);
};

template <typename ... Args>
using EmptyCallable = decltype([](Args ...){});

template <Callable<int, string> T = EmptyCallable<int, string>>
void f(T t = {})
{
  t(1, "Hello!");
}

void
foo(int, string)
{
}

int main()
{
  f(foo);
}
