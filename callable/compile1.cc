int
foo(int i)
{
  return ++i;
}

int
main()
{
  // The callable is a pointer to a function.
  auto f = foo;
  return f(1);
}
