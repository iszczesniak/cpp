int main()
{
  int x = 1;
  ++++x; // OK: ++x is an lvalue, and ++ wants an lvalue.
  // x++++; // Error: x++ is an rvalue, and ++ wants an lvalue.
}
