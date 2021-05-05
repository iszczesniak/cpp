auto f1()
{
  return 0;
}

auto f2()
{
  static int i = 0;
  return i;
}

auto &f3()
{
  static const int i = 0;
  return i;
}

int main()
{
  f1();

  // This will not compile, because f2 returns int, an rvalue.
  // ++f2();
  int &&r2 = f2();

  // This will not compile, because f3 returns an lvalue reference of
  // the const int type.  
  const int &r3 = f3();
}
