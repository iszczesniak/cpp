using callable = decltype([]{});

template <typename C = callable>
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
