int
main()
{
  // These two are equivalent.
  [](){};
  []{};

  // Here we also call the closure: notice the trailing ().
  []{}();
}
