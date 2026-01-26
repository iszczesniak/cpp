struct A
{
  void foo();
};

struct B: A
{
  using A::foo;
  void foo(int);
};

int main()
{
  B b;
  b.foo();
  // b.A::foo();
}
