class B;

B &
boo()
{
  return *static_cast<B *>(0);
}

int main()
{
  &boo(); // OK: "boo()" is an lvalue.
  // B(); // Error: expression "B()" is an rvalue.
}
