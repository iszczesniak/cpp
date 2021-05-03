void foo()
{
}

int
main()
{
  const volatile int x = 1;

  // A pointer to a variable.
  // auto = const volatile int
  auto *r1 = &x;
  // auto = volatile int
  const auto *r2 = &x;
  // auto = const int
  volatile auto *r3 = &x;
  // auto = int
  const volatile auto *r4 = &x;

  // A reference to a function.
  // auto = void()
  auto *f1 = foo;
  // The above is equivalent to this.
  using ft = void();
  ft *f2 = foo;

  // A reference to a C-style table.
  int t[] = {1, 2, 3};
  // auto = int[3]
  auto *t1 = &t;
  // The above is equivalent to this.
  using t3i = int[3];
  t3i *t2 = &t;
}
