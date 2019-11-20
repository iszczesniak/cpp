struct T
{
  // The copy assignment operator.
  T &operator = (const T &t)
  {
    // Copy the data from object t to *this.
    return *this;
  }

  // The move assignment operator.
  T &operator = (T &&t)
  {
    // Move the data from object t to *this.
    return *this;
  }
};
