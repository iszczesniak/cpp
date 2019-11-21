struct A
{
  // We need to include the default constructor, because the
  // definition of the argument constructor below would inhibit the
  // generation of the default constructor.
  A() = default;

  A(int x)
  {
  }
};

int
main()
{
  A a, b(1);
}
