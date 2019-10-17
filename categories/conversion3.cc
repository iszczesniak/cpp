int main()
{
  int *p = static_cast<int *>(0);
  // &static_cast<int *>(0); // Error: lvalue required.
  // &nullptr; // Error: lvalue required.
}
