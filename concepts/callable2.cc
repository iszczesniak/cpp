#include <functional>
#include <iostream>
#include <string>

using namespace std;

template <typename F, typename ... Args>
concept Callable = requires(F f, Args ... args)
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
foo(int i, string s)
{
  cout << "foo: " << i << ", " << s << endl;
}

struct A
{
  void
  operator()(int i, string s)
  {
    cout << "A: " << i << ", " << s << endl;
  }
};

int main()
{
  // The function is called with a default-constructed EmptyCallable.
  f();

  // Error: the constraint of the concept not satisfied: the closure
  // (i.e., its call operator) accepts no argument, while it should
  // accept an int and a string.
  // f([]{});

  f(foo);
  f(function(foo));

  f([](int i, string s)
    {cout << "lambda: " << i << ", " << s << endl;});
  f(function([](int i, string s)
    {cout << "lambda: " << i << ", " << s << endl;}));

  f(A());
  f(function(A()));
}
