int main()
{
  struct A
  {
    void
    operator = (int i) &
    {
    }

    void
    operator = (int i) && = delete;
  };

  A a;
  a = 1;

  // Does not compile, because the overload declared deleted.
  // A() = 1;
}
