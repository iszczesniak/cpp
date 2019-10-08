int &
loo()
{
  // It compiles even without the return statement!
  // return *static_cast<int *>(0);
  return *((int *)0);
}

int main()
{
  &loo(); // OK: "loo()" is an lvalue.
  int &l = loo(); // OK: "loo()" is an lvalue.
}
