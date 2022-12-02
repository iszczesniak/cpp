struct A
{
  int m_a;
  
  A(int a): m_a(a)
  {
  }

  bool
  operator < (const A &a) const
  {
    return this->m_a < a.m_a;
  }
};

// Uncomment to see the ambiguity error.
// bool
// operator < (const A &a1, const A &a2)
// {
//   return a1.m_a < a2.m_a;
// }

int
main()
{
  A a1(1), a2(2);

  a1 < a2;
}
