class B;

B &
boo()
{
}

int main()
{
  B &br = boo();
  // B(); - błąd, bo r-wartość
}
