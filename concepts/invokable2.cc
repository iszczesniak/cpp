#include <concepts>
#include <functional>
#include <string>

using namespace std;

template <typename T, invocable<T> F>
void
call(T &&t, F &&f)
{
  forward<F>(f)(forward<T>(t));
}

void
foo(float)
{
}

void
soo(string)
{
}

int
main()
{
  // Two conversions take place here:
  // * int -> float,
  // * const char (&)[7] -> string
  //
  // Where do they exactly take place?
  call(1, foo);
  call("Hello!", soo);
}
