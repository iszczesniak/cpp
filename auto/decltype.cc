int &foo()
{
  static int i = 1;
  return i;
}

int main()
{
  double a = 0.1;
  decltype(a) b = 1;

  int i, j = 1;
  int &x = i;

  decltype(x) y = j;
}
