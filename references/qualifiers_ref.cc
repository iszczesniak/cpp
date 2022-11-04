int main()
{
  int x = 1;
  const int cx = 2;

  // A reference to an integer.
  int &r2i_1 = x;
  // A reference to an integer cannot point to a const integer, because
  // then we could modify the integer that we declare const.
  // int &r2i_2 = cx;

  // A reference to a const integer.
  const int &r2ci = x;

  // A const-qualified reference type to an integer does not exist.
  // int & const cr2i = x;
  // Nor a const-qualified reference type to a const integer.
  // const int & const cr2ci = x;
  // Nor any other cv-qualified reference type.
  // const volatile int & const volatile cvr2cvi = x;
}
