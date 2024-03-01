#include <iostream>

template <unsigned I, typename T>
T
power(T t)
{
  if constexpr (I)
    return t * power<I - 1>(t); 

  return 1;
}

int
main()
{
  // The value calculated at compile-time, nothing at run-time.
  std::cout << power<2>(.2) << std::endl;

  // We use the volatile qualifier to force evaluation at run-time.
  volatile int d = 3;
  // The assemby code uses the value of d without any calculation.
  std::cout << power<1>(d) << std::endl;

  // The assemby code just multiplies d by itself.
  std::cout << power<2>(d) << std::endl;
}
