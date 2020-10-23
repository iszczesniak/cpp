int
main()
{
  // The block scope is here, so that a behaves like a temporary
  // object.  Object a is of anonymous type.
  {
    struct
    {
      void
      operator()() const
      {
      }
    } a;
    a();
  }
}
