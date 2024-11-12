int main()
{
  int a1 = 1;
  const int a2 = 2;
  volatile int a3 = 3;
  const volatile int a4 = 4;

  // The commented lines below would bypass the qualifiers.

  int & p11 = a1;
  // int & p12 = a2;
  // int & p13 = a3;
  // int & p14 = a4;

  const int & p21 = a1;
  const int & p22 = a2;
  // const int & p23 = a3;
  // const int & p24 = a4;

  volatile int & p31 = a1;
  // volatile int & p32 = a2;
  volatile int & p33 = a3;
  // volatile int & p34 = a4;

  const volatile int & p41 = a1;
  const volatile int & p42 = a2;
  const volatile int & p43 = a3;
  const volatile int & p44 = a4;
}
