#include <iostream>

// This example demonstrates that we need a function object, then
// defaulted, to get a default comparison function.

// This function will be optimzed out, sometimes at compile time - it
// will not be even called.

// Even if we call it like this, the function will be optimized out
// anyway:
//
// int i = 1, j = 2;
// compare(i, j);

// If we try to say:
//
// volatile int i = 1, j = 2;
//
// The example will not compile, because the type qualifiers i and j
// should have the same or less type qualifiers (cv-qualified) than
// the parameter types of the template function.

// We can see how the function is optimized out, and the code is
// inlined, when we just pass by value, i.e.,
//
// compare(T a, T b, F f = {})

template <typename T, typename F = std::less<T>>
bool
compare(const T &a, const T &b, F f = {})
{
  return f(a, b);
}

int
main()
{
  std::cout << std::boolalpha << compare(1, 2) << std::endl;
}
