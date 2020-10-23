int
main()
{
  struct A
  {
    void
    operator()() const
    {
    }
  };

  A a;
  a();
}
