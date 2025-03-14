int main()
{
  struct A
  {
    void operator = (this A &, int)
    {
    }

    void operator = (this A &&, int) = delete;
  };

  A a;
  a = 1;

  // Does not compile, because the overload declared deleted.
  // A() = 1;
}
