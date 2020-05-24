void g(const int &)
{
}

template <typename T>
void f(T &t)
{
  g(t);
}

struct A
{
};

int main()
{
  // We can call "g" all right with an rvalue.
  g(1);
  // But we cannot call "f" with an rvalue.
  // f(1);

  // This doesn't compile either.
  // f(A());
}
