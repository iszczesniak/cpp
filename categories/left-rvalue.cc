int main()
{
  struct A
  {
    void
    operator = (int i)
    {
    }
  };

  A() = 1;
  A().operator=(1);
}
