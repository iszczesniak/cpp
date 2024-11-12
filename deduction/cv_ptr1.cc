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
  int i = 1;
  int * const p1 = &i;
  int * p2 = p1;
  
  foo(p1);
  foo(p2);
}
