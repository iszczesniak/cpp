struct A {};
struct B: A {};

A foo()
{
  B b;
  return b;
}

int
main()
{
}
