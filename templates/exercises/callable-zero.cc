template <typename C = decltype([]{})>
void
foo(C c = {})
{
  c();
}

int
main()
{
  foo();
}
