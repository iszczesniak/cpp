int
main()
{
  // The callable is a closure.
  auto f = [](int i){return ++i;};
  volatile int i = 1;
  return f(i);
}
