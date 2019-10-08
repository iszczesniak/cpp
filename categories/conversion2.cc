int main()
{
  // The dereference operator requires an rvalue.
  *((int *)0); // OK: "(int *)0" is a null pointer and an rvalue.

  int x = 1;
  int *p = &x;
  *p; // OK: "p" is an lvalue, but converted to an rvalue.
}
