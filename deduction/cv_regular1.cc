int main()
{
  int a1 = 1;
  const int a2 = 2;
  volatile int a3 = 3;
  const volatile int a4 = 4;

  int b1 = a4;
  const int b2 = a3;
  volatile int b3 = a2;
  const volatile int b4 = a1;
}
