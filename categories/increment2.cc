int main()
{
  int x = 1;
  ++++x; // OK
  // x++++; // Error x++ is an rvalue, and <expr>++ wants an lvalue.
}
