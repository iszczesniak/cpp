int main()
{
  struct A
  {
    void operator = (int) &
    {
    }

    void operator = (int) && = delete;
  };

  A a;
  a = 1;

  // Does not compile, because the overload declared deleted.
  // A() = 1;
}
