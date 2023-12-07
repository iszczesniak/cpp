struct A
{
  // Non-const *this because the trailing const is commented out.
  bool operator == (const A &) // const
  {
  }
};

int main()
{
  A a1;
  const A a2;
  // This compiles, because a1 is non-const.
  a1 == a2;
  // The following compiles since C++20, because the expression "a2 ==
  // a1" is rewritten to "a1 == a2".
  a2 == a1;
}
