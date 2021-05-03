double foo()
{
  return .0;
}

int * goo()
{
  return static_cast<int *>(0);
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
}
