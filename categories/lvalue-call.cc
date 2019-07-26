int &
loo()
{
  // Dlaczego może się kompilować bez instrukcji return?
  // return *((int *)0);
  // return *static_cast<int *>(0);
}

int main()
{
  &loo(); // OK, bo l-wartość.
  int &l = loo(); // OK, bo l-wartość.
}
