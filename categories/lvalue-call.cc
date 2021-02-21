int &
loo()
{
  // FYI: It compiles even if we remove the return statement below!
  return *static_cast<int *>(0);
}

int main()
{
  &loo(); // OK: "loo()" is an lvalue.
  int &l = loo(); // OK: "loo()" is an lvalue.
}
