int
inc(int i)
{
  return ++i;
}

int
dec(int i)
{
  return --i;
}

int
main()
{
  // Will it be true or false?
  volatile bool flag;

  // The callable is a pointer to a function.
  auto f = flag ? dec : inc;
  return f(1);
}
