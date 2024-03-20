struct A
{
  // We need this volatile to prevent the compiler from optimizing
  // everything out.  But this also prevents the compiler from
  // optimizing out the nullptr assignments.
  int * volatile m_p;

  A(int *p): m_p(p)
  {
  }

  A(A &&src): m_p(src.m_p)
  {
    src.m_p = nullptr;
  }

  A &
  operator = (A &&src)
  {
    m_p = src.m_p;
    src.m_p = nullptr;
    return *this;
  }
};

int
main()
{
  int x = 1, y = 2;
  A a1(&x), a2(&y);
  // A tmp = std::move(a1);
  // a1 = std::move(a2);
  // a2 = std::move(a1);
  std::swap(a1, a2);
}
