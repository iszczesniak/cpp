struct A
{
  bool operator == (const A &) const
  {
    return true;
  }
};

bool operator == (const A &, const A &)
{
  return true;
}

int main()
{
  A a1;
  const A a2;
  // The following calls: a1.operator=(a1).  This compiles, because a1
  // is non-const.
  a1 == a2;
  // The following compiles since C++20, because the expression "a2 ==
  // a1" is rewritten to "a1 == a2".
  a2 == a1;
}
