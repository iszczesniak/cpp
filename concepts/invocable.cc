#include <concepts>
#include <iostream>
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
foo(int i, string s)
{
  cout << "foo: " << i << ", " << s << endl;
}

int main()
{
  f();
  f(foo);
}
