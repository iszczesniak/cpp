struct A
{
  // We need this volatile to prevent the compiler from optimizing
  // everything out.
  int * volatile m_p;

  A(int *p): m_p(p)
  {
  }
};

int
main()
{
  int x, y;
  A a1(&x), a2(&y);
  int *tmp = a1.m_p;
  a1.m_p = a2.m_p;
  a2.m_p = tmp;
}
