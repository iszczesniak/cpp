int main()
{
  const int i = 1;
  &i; // OK: "i" is an lvalue.
  // i = 2; // Error, even though "i" is an lvalue.
}
