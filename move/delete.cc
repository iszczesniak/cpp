struct A
{
  // Konstruktor kopiujący.
  A(const A &) = delete;

  // Kopiujący operator przypisania.
  A &
  operator =(const A &) = delete;
};
