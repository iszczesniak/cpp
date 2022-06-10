#include <concepts>
#include <iostream>
#include <string>

using namespace std;

template <typename ... Args>
using EmptyCallable = decltype([](Args ...){});

template <typename T = EmptyCallable<int, string>>
void f1(T t = {}) requires invocable<T, int, string>
{
  t(2, "Hello!");
}

template <invocable<int, string> T = EmptyCallable<int, string>>
void f2(T t = {})
{
  t(1, "Hello!");
}

void f3(invocable<int, string> auto t = EmptyCallable<int, string>{})
{
  t(3, "Hello!");
}

void
foo(int i, string s)
{
  cout << "foo: " << i << ", " << s << endl;
}

int main()
{
  f1();
  f1(foo);
  f2();
  f2(foo);

  // The following should compile, I reckon, because the variable t
  // below (which is just like the parameter of function f3) compiles
  // fine.  Yet, it doesn't with GCC 12.1.0.

  // f3();

  invocable<int, string> auto t = EmptyCallable<int, string>{};

  f3(foo);
}
