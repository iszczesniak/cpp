#include <concepts>

void foo(int i)
{
}

// This function has same signature as the one above.
// void foo(const int i)
// {
// }

int main()
{
  const int i1 = 1;
  int const i2 = 2;
  static_assert(std::same_as<const int, int const>);
  foo(i1);
}
