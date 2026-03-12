struct A
{
  A() = default;
  A(A &&) = delete;
};

A foo()
{
  return A();
}

int
main()
{
  A a = foo();
}
