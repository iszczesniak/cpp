int main()
{
  // static_cast<int *>(0) and nullptr are null-value literals of a
  // pointer type.  They both are rvalues.

  // &static_cast<int *>(0); // Error: lvalue required.

  // &nullptr; // Error: lvalue required.
}
