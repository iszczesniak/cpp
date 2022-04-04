double foo()
{
  return .0;
}

int *goo()
{
  return static_cast<int *>(0);
}

int &loo()
{
  static int l;
  return l;
}

int
main()
{
  // auto = int
  auto w = 1;
  // auto = int
  const auto x = 2;
  // auto = int
  auto y = w;
  // auto = int
  auto z = x;

  // auto = double
  auto a = foo();
  // auto = int *
  auto b = goo();

  // auto = double (*)()
  auto fp = foo;

  int t[] = {1, 2, 3};
  // auto = int *
  auto tp = t;

  // auto = const char *
  auto hw = "Hello World!";

  // auto = int
  auto l = loo();
}
