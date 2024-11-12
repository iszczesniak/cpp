void foo(int *)
{
}

// This function has same signature as the one above.
// void foo(int * const)
// {
// }

int main()
{
  int i = 1;
  int * p1 = &i;
  int * const p2 = &i;

  foo(p1);
  foo(p2);
}
