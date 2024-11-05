#include <concepts>

void foo(const int * i)
{
}

// This function has same signature as the one above.
// void foo(const int * const i)
// {
// }

int main()
{
  int i = 1;
  foo(&i);

  const int j = 2;
  foo(&j);

  int * const p1 = &i;
  const int * p2 = p1;
  
  const int * p3 = &i;
  // Error! Would allow to modify the data pointed by p3.
  // int * const p4 = p3;
}
