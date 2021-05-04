auto f1()
{
  return 0;
}

auto f2()
{
  static int i = 0;
  return i;
}

decltype(auto) f3()
{
  static int i = 0;
  return i;
}

int main()
{
  f1();

  // This will not compile, because f2 returns int.
  // ++f2();
  
  ++(f3());
}
