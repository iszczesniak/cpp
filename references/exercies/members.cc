struct A
{
  volatile int &m_r;

  A(volatile int &r): m_r(r)
  {
  }
};

int
main()
{
  volatile int i;
  A a(i);
  a.m_r = 1;
}
