struct A
{
  A() = default;
  // Explicitly deletes the move-ctor, and implicitly the copy-ctor.
  A(A &&) = delete;
};

int
main()
{
  try
    {
      throw A();
    }
  catch (A a)
    {
    }
}
