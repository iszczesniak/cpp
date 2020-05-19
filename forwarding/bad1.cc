void g(const int &)
{
}

template <typename T>
void f(T &p)
{
  g(p);
}

int main()
{
  // We can call "g" all right with an rvalue.
  g(1);
  // But we cannot call "f" with an rvalue.
  f(1);
}
