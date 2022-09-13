struct A
{
  A() = default;
  A(A &&) = delete;
};

A foo(A)
{
  return A();
}

int
main()
{
  A a = foo(A());
}
