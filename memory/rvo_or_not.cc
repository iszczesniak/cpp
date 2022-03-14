struct A
{
  A() = default;
  A(const A &) = delete;
  A(A &&) = delete;
};

A foo(A a)
{
  return A();
}

int
main()
{
  A a = foo(A());
}
