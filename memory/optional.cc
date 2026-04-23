struct X
{
  X() = default;
  // X(const X &) = delete;
};

X f()
{
  X x;
  return x;
}

int main()
{
  X x = f();
}
