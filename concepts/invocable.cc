#include <concepts>
#include <string>

using namespace std;

template <typename ... Args>
using EmptyCallable = decltype([](Args ...){});

template <invocable<int, string> T = EmptyCallable<int, string>>
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
  f();
  f(foo);
}
