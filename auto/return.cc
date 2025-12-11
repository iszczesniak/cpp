// auto = int[3]
auto &f1()
{
  static int t[] = {1, 2, 3};
  return t;
}

void foo()
{
};

auto *f2()
{
  return foo;
}

// auto = const int *
auto f3()
{
  static const int i = 0;
  return &i;
}

int main()
{
  // Function f1 returns an lvalue reference to a table of 3 integers,
  // and so we are able to initialize the reference below.
  int (&f1r1)[3] = f1();
  // The following is equivalent to the above.
  using f1t = int[3];
  f1t &f1r2 = f1();

  // We get a pointer to a function.
  void (*f)() = f2();

  // Here we just get a pointer to a const int.
  const int *r3 = f3();
}
