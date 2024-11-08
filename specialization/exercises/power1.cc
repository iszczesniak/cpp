#include <iostream>

template <unsigned I, typename T>
T
power(T t)
{
  return t * power<I - 1>(t);
}

// This solution is inferior to using the conditional compile-time
// statement (if constexpr) because we have to define a specialization
// for every type: double and int.
template <>
double power<0>(double t)
{
  return 1;
}

template <>
int power<0>(int t)
{
  return 1;
}

int
main()
{
  // The value calculated at compile-time, nothing at run-time?
  std::cout << power<2>(.2) << std::endl;

  // We use the volatile qualifier to force evaluation at run-time.
  volatile int d = 3;
  // The assemby code uses the value of d without any calculation.
  std::cout << power<1>(d) << std::endl;

  // The assemby code just multiplies d by itself.
  std::cout << power<2>(d) << std::endl;
}
