template <typename T>
T
max_ref(const T &a, const T &b)
{
  return b < a ? a : b;
}

template <typename T>
T
max_val(T a, T b)
{
  return b < a ? a : b;
}

double
MAX(const double &a, const double &b)
{
  return b < a ? a : b;
}

int
main()
{
  // 1 is converted to .1 (which is a temporary, an rvalue), so that a
  // const reference to double (the first parameter) can bind to it.
  MAX(1, .1);

  // The following call to a template function fails, because:
  //
  // * no conversion is allowed, so 1 cannot be converted to .1.
  // 
  // * T is first deduced int, then double, so deduction fails.

  // max_ref(1, .1);
  // max_val(1, .1);
  
  // No deduction takes place.
  max_ref<int>(1, '1');
  max_ref<double>(1, .1);
  max_val<int>(1, '1');
  max_val<double>(1, .1);
}
