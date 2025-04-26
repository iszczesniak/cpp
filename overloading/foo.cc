void foo(int &, const int &);
void foo(const int &, int &);

int
main()
{
  int x;
  // foo(x, x);
}
