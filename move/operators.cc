struct T
{
  // Kopiujący operator przypisania.
  T &operator = (const T &t)
  {
    // Skopiuj dane z obiektu t do *this.
    return *this;
  }
  // Przenoszący operator przypisania.
  T &operator = (T &&t)
  {
    // Przenieś dane z obiektu t do *this.
    return *this;
  }
};
