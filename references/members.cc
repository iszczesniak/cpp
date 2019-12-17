struct A
{
  int &m_i;

  A(int &i): m_i(i)
  {
  }
};

int
main()
{
  int i;
  A a(i);
}
