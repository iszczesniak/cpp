struct A
{
  constexpr A() = default;
};

int
main()
{
  // Is the identity the same as the address?
  
  const int i1 = 1;
  const int i2 = 1;
  static_assert(i1 == i2);
  // Addresses of i1 and i2 differ.
  static_assert(&i1 != &i2);

  constexpr int I1 = 1;
  constexpr int I2 = 1;
  static_assert(I1 == I2);
  // Addresses of I1 and I2 differ.
  static_assert(&I1 != &I2);

  constexpr A a1, a2;
  // Addresses of a1 and a2 differ.
  static_assert(&a1 != &a2);
  
  // What's the identity anyway?
}
