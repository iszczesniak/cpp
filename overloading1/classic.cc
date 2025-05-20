void foo(const int &, int &);
void foo(int &, const int &);

int main()
{
  int x;
  // Ambiguous call.
  // foo(x, x);
}
