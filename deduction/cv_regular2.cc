void foo(int)
{
}

// This function has same signature as the one above even though their
// parameters differ with the qualifiers.
// void foo(const int)
// {
// }

int main()
{
  const int i = 1;
  foo(i);

  // Can point to a function with a regular parameter that is either
  // const or non-const.
  void (*fp1)(const int) = foo;
  void (*fp2)(int) = foo;
}
