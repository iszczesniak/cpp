void foo(const int)
{
}

// The definition of a function defined above.
// void foo(int)
// {
// }

int
main()
{
  foo(1);
  // Can point to a function with a regular parameter that is either
  // const or non-const.
  void (*fp)(int) = foo;
}
