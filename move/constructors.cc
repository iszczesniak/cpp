struct T
{
  // Konstruktor kopiujący.
  T(const T &t)
  {
    // Skopiuj dane z obiektu t do *this.
  }

  // Konstruktor przenoszący.
  T(T &&t)
  {
    // Przenieś dane z obiektu t do *this.
  }
};
