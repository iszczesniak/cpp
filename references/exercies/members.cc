struct A
{
  volatile int &m_i;

  A(volatile int &i): m_i(i)
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
