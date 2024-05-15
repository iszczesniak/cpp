struct A
{
  static const A a1;
  static const A a2;
};

int
main()
{
  static_assert(&A::a1 != &A::a2);
}
