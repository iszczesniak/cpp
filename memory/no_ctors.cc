struct A
{
  A() = default;
  A(const A &) = delete;
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
