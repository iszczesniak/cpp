struct A
{
  void foo();
};

struct B: A
{
  void foo(int);
};

int main()
{
  B b;
  // b.foo();
  b.A::foo();
}
