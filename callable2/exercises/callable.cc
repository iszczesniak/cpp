template <typename F = decltype([]{})>
void foo(F f = {})
{
  f();
}

int
main()
{
  foo();
}
