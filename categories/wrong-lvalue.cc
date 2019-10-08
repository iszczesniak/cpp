int main()
{
  const int i = 1;

  &i; // Expression "i" is an lvalue.
  // &2; // Expression "2" is an rvalue.

  // i = 2; // Error, even though "i" is an lvalue.
}
