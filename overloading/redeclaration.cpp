struct A
{
  void foo(this const A &);
  // Redeclaration.
  // void foo() const &;
};
