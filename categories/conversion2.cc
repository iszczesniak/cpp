int main()
{
  // The dereference operator requires an rvalue.
  *static_cast<int *>(0); // OK: A null pointer literal, an rvalue.

  int x = 1;
  int *p = &x;
  *p; // OK: "p" is an lvalue, but converted to an rvalue.
}
