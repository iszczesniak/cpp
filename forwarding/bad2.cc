void g(int &)
{
}

template <typename T>
void f(const T &t)
{
  g(t);
}

int main()
{
  int x = 1;
  // We can call "g" with an lvalue of non-const type.
  g(x);

  // We cannot call "f" with an lvalue of non-cost, because in "f"
  // it's bound to a const lvalue reference, which cannot be used to
  // initialize the parameter of g, which is a non-const lvalue
  // reference.
  // f(x);
}
