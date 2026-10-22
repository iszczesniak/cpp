struct X
{
  X() = default;
  // X(const X &) = delete;
};

X f()
{
  X x;
  return x; // for named elision
  // return X(); // for unnamed elision
}

int main()
{
  f();
}
