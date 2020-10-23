int
main()
{
  // The block scope is here, so that object x behaves like a
  // temporary object.  Object a is of anonymous type.
  {
    struct
    {
      void
      operator()() const
      {
      }
    } x;
    x();
  }
}
