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

A goo()
{
  return foo();
}

int main()
{
  A a = goo();
}
