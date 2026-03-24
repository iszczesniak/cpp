struct A
{
  A() = default;
  // A(const A &) = delete;
  // A(A &&) = delete;
};

A f()
{
  A a;
  return a;
}

int main()
{
  A a = f();
}
