struct A
{
  A() = default;
  // Explicitly delete the copy-ctor (the move-ctor is implicitly left
  // undeclared).
  A(const A &) = delete;
};

int
main()
{
  // The constructor elision takes place, because the code compiles.
  // The thrown object is constructed in place of variable a.
  try
    {
      throw A();
    }
  catch (A a)
    {
    }
}
