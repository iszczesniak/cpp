template <typename T>
struct ER;

int main()
{
  const int a = 1;

  // Here we're dropping the const qualifier.
  const_cast<int &>(a) = 2;

  // Here we're also dropping the const qualifier.  When we
  // dereference a pointer, we get an lvalue.  So we've got an lvalue
  // of the integer type to which we can assign the value of 3.  The
  // compiler is encoding the category in the type of the expression:
  // int &.
  *const_cast<int *>(&a) = 3;

  // The type of the dereference expression is a reference.
  int *p;
  ER<decltype(*p)> er;
}
