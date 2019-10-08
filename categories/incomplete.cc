class B;

B &
boo()
{
}

int main()
{
  B &br = boo();
  // B(); // Error: expression "B()" is an rvalue.
}
