struct X
{
  X() = default;
  X(const X &) = delete;
  X(X &&) = delete;
};

X f()
{
  return X();
}

int main()
{
  X x = f();
}
