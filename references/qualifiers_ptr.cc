int main()
{
  int x = 1;
  const int cx = 2;

  // A pointer to an integer.
  int *p2i_1 = &x;
  // A pointer to an integer cannot point to a const integer, because
  // then we could modify the integer that we declare const.
  // int *p2i_2 = &cx;

  // A pointer to a const integer.
  const int *p2ci_1 = &x;
  const int *p2ci_2 = &cx;

  // A const pointer to an integer.
  int * const cp2i = &x;
  // We can modify the data pointed to by the pointer all right.
  *cp2i = 2;
  // But not the pointer itself.
  // cp2i = &x;

  // Const pointer to a const integer.
  const int * const cp2ci_1 = &x;
  const int * const cp2ci_2 = &cx;
  // We cannot modify the data:
  // *cp2ci_1 = 2;
  // Nor the pointer itself:
  // cp2ci_1 = &cx;

  // The same applies for the volatile qualifier.
  const volatile int * const volatile cvp2cvi = &x;
}
