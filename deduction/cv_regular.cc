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
  static_assert(std::same_as<const int, int const>);
  const int i = 1;
  foo(i);
}
