namespace X
{
  struct A {};

  void f(A, int);
}

namespace Y
{
  void f(X::A, unsigned);

  void g()
  {
    X::A a;
    f(a, 1);
  }
}
