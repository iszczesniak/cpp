int
main()
{
  int x = 1;
  const int y = 2;

  // This becomes an lvalue reference, because auto = int &
  auto &&lr = x;
  // This becomes a const reference, because auto = const int &
  auto &&cr = y;
  // This becomes an rvalue reference, because auto = int
  auto &&rr = 1;
}
