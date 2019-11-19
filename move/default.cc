struct A
{
  ~A()
  {
  }
  
  // A(const A &) = default;
};

int
main()
{
  A a;
  A b(a);
}
