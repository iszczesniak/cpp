#include <concepts>

void foo(int * i)
{
}

// This function has same signature as the one above.
// void foo(int * const i)
// {
// }

int main()
{
  const int i = 1;
  int * const p1 = nullptr;
  // int * const p2 = &i; // Error: Would let modify i.
  foo(p1);
}
