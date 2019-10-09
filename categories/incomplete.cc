class B;

B &
boo()
{
}

int main()
{
  &boo(); // OK: "boo()" is an lvalue.
  // B(); // Error: expression "B()" is an rvalue.
}
