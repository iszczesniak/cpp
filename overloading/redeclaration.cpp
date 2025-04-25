struct A
{
  void foo(this const A &);
  void foo() const &;
};
