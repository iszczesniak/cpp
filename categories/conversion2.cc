int main()
{
  // The dereference operator requires an rvalue.  The null pointer
  // literal static_cast<int *>(0) is an rvalue.
  *static_cast<int *>(0);

  int x = 1;
  int *p = &x;
  *p; // OK: "p" is an lvalue, but converted to an rvalue.
}
