struct X
{
  A m_a;

  X(A a): m_a(a)
  {
  }
};

int main()
{
  X(A());
}
